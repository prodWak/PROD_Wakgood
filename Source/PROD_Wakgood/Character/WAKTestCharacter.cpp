// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character\WAKTestCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AbilitySystem\WAKASC.h"
#include "AbilitySystem\WAKAttributeSet.h"
#include "WAKDataTable.h"
#include "Input/WAKInputComponent.h"
#include "WAKTag.h"
#include "Engine/DataTable.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Abilities/WakGA_HitReact.h"
#include "AbilitySystem/Abilities/WakGA_RangedAttackBase.h"
#include "AbilitySystem/Abilities/WakGA_RangedAttackTest.h"
#include "AbilitySystem/Abilities/Normal/WakGA_Catch.h"
#include "AbilitySystem/Abilities/Normal/WAKGA_FormChangeNormal.h"
#include "AbilitySystem/Abilities/Normal/WakGA_NormalAttack1.h"
#include "Player/WakPlayerState.h"

//////////////////////////////////////////////////////////////////////////
// AWAKTestCharacter

AWAKTestCharacter::AWAKTestCharacter() 
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	ASC = CreateDefaultSubobject<UWAKASC>("ASC");
	AttributeSet = CreateDefaultSubobject<UWAKAttributeSet>("AttributeSet");

	
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");

	//Weapon->SetupAttachment(GetMesh(),FName("hand_r_weapon"));
	
	
	
	WeaponCollision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	WeaponCollision->SetupAttachment(Weapon);
	WeaponCollision->SetCapsuleHalfHeight(30.f);
	WeaponCollision->SetGenerateOverlapEvents(true);
	
	//Weapon->OnComponentBeginOverlap.AddDynamic(this,&AWAKTestCharacter::OnWeaponBeginOverlap);

	//Weapon->SetStaticMesh("");
	
	/*static ConstructorHelpers::FObjectFinder<UDataTable> ObjectFinder(TEXT("/Script/Engine.DataTable/Game/DataTable/DT_WeaponData.DT_WeaponData"));
	if(ObjectFinder.Succeeded())
	{
		WeaponMeshDataTable = ObjectFinder.Object;
	}*/
	CharacterType = FWAKGameplayTags::Get().Character_Type_Normal;

	ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageFinder(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Slash.AM_Slash'"));
	if(AttackMontageFinder.Succeeded())
		NormalAttackAnim = AttackMontageFinder.Object;

	ConstructorHelpers::FObjectFinder<UDataTable> StatusFinder(TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_CharacterStatus.DT_CharacterStatus'"));
	if(StatusFinder.Succeeded())
		CharacterStatusDT = StatusFinder.Object;
}

void AWAKTestCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

	ASC->InitAbilityActorInfo(this,this);
	
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,true);
	Weapon->AttachToComponent(GetMesh(),TransformRules,FName("hand_r_weapon"));
	Weapon->SetGenerateOverlapEvents(false);

	ASC->RegisterGameplayTagEvent(FWAKGameplayTags::Get().Effects_HitReact,EGameplayTagEventType::NewOrRemoved).AddUObject(
		this,&AWAKTestCharacter::HitReactTagChange);

	OnNextAttackCheck = new FOnNextAttackCheck();
	NotifyEnd = new FOnNotifyEnd();
	NormalCharacterStatus = CharacterStatusDT->FindRow<FCharacterStatus>(FName("Normal"),TEXT(""));

	if(IsPlayerControlled())
		Cast<UWAKASC>(ASC)->AddCharacterAbilities(NormalCharacterStatus->MoveSet);
}

void AWAKTestCharacter::ApplyEffectToTarget(AActor* OtherActor, TSubclassOf<UGameplayEffect> EffectClass)
{
	if(OtherActor)
	{
		check(DamageEffect);
		UAbilitySystemComponent* EnemyASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
		UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage(),EffectClass);
		if (EnemyASC == nullptr) return;
		FGameplayEffectContextHandle EffectHandle = ASC->MakeEffectContext();
		EffectHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass,1,EffectHandle);
		FActiveGameplayEffectHandle ActiveHandle = ASC->ApplyGameplayEffectToTarget(Effect,EnemyASC,UGameplayEffect::INVALID_LEVEL,EffectHandle);
		
		/*
		FGameplayEffectContextHandle EffectContextHandle = EnemyASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = EnemyASC->MakeOutgoingSpec(DamageEffect, 1, EffectContextHandle);
		Enemy->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
		*/
	}
	
}

void AWAKTestCharacter::HitReactTagChange(const FGameplayTag CallbackTag, int32 NewCount)
{
	//HitReact Tag 부여시 자동 실행. 
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	TSubclassOf<UGameplayAbility> HitReactAbilityClass =UWakGA_HitReact::StaticClass(); 
	if(bHitReacting)
	{
		ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(FWAKGameplayTags::Get().Effects_HitReact)); //HitReact 어빌리티 실행.
	}
}

UAbilitySystemComponent* AWAKTestCharacter::GetAbilitySystemComponent() const
{
	return ASC; 
}


void AWAKTestCharacter::SetWeaponOverlap(bool CanOverlap)
{
	Weapon->SetGenerateOverlapEvents(CanOverlap);
	Weapon->SetCollisionProfileName(FName("OverlapAll"));
}

void AWAKTestCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float Level)
{
	check(IsValid(ASC));
	check(Effect);
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(Effect,Level,ContextHandle);
	const FGameplayEffectSpec* GameplayEffect(EffectSpecHandle.Data.Get());
	ASC->ApplyGameplayEffectSpecToSelf(*GameplayEffect);
}

void AWAKTestCharacter::InitializeAttributeToEffect()
{
	check(PrimaryEffect);
	//Primary Effect를 데이터 테이블에 만듫고 캐릭터와 몬스터에 태그를 붙여서 초기화 하는걸로.
	ApplyEffectToSelf(PrimaryEffect,1.f);
}

void AWAKTestCharacter::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != this)
	{
		ApplyEffectToTarget(OtherActor,DamageEffect);
	}
}

void AWAKTestCharacter::HealthCheck()
{
	float Health = AttributeSet->GetHealth();
	UE_LOG(LogTemp,Warning,TEXT("After Effect Health : %f"),Health);
	HealthChangeDelegate.Broadcast(Health); // UI 등에서 사용 가능. 
	if(Health < 0)
	{
		//죽음 어빌리티 실행.
		/*FGameplayAbilitySpec AbilitySpec(UWakGA_Dead::StaticClass(),1);
		AbilitySpec.SourceObject = this;
		FGameplayAbilitySpecHandle AbilitySpecHandle = ASC->GiveAbility(AbilitySpec);
		ASC-> GiveAbilityAndActivateOnce(AbilitySpecHandle);*/
	}
}

UAnimMontage* AWAKTestCharacter::GetReactMontage()
{
	return ReactMontage;
}

void AWAKTestCharacter::Die()
{
	//무기를 떨어뜨림.
	Weapon->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Weapon->SetSimulatePhysics(true); 
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetSimulatePhysics(true); // 레그돌로
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//LifeSpan초에 걸쳐 Resolve 시키기
	
}

void AWAKTestCharacter::SetNormalMode()
{
	FGameplayAbilitySpec AbilitySpec(UWAKGA_FormChangeNormal::StaticClass(),1);
	AbilitySpec.SourceObject = this;
	FGameplayAbilitySpecHandle AbilitySpecHandle = ASC->GiveAbility(AbilitySpec);
	ASC->TryActivateAbility(AbilitySpecHandle);
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Try Normal Mode activate"));
	
}

void AWAKTestCharacter::NormalAttack()
{
	TSubclassOf<UGameplayAbility> NormalAttackAbility =UWakGA_NormalAttack1::StaticClass();
	/*UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if(AnimInstance->Montage_IsPlaying(NormalAttackAnim)) // NormalAttack이 실행 중이라면
	{
		if(AnimInstance->Montage_GetCurrentSection(NormalAttackAnim) == FName("Attack1"))
			AnimInstance->Montage_JumpToSection(FName("Attack2"));
		else if(AnimInstance->Montage_GetCurrentSection(NormalAttackAnim) == FName("Attack2"))
			AnimInstance->Montage_JumpToSection(FName("Attack3"));
	}*/

	if(IsValid(NormalAttackAbility))
	{
		UE_LOG(LogTemp,Warning,TEXT("Ability Is Valid"));
	}
	FGameplayAbilitySpec AbilitySpec(NormalAttackAbility);
	AbilitySpec.SourceObject = this;
	AbilitySpec.InputID = 1;
	FGameplayAbilitySpecHandle AbilitySpecHandle = ASC->GiveAbility(AbilitySpec);
	
	ASC->AbilityLocalInputPressed(1);
	ASC->TryActivateAbility(AbilitySpecHandle); //이미 Activate 중이라면 어처피 다시 Activate 되지 않을 것. 
	
	/*
	FGameplayTagContainer NormalAttack1Container = FGameplayTagContainer();
	NormalAttack1Container.AddTag(FWAKGameplayTags::Get().Ability_Skill_1);
	bool IsActive = ASC->TryActivateAbilitiesByTag(NormalAttack1Container,false);
	*/
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Try Normal Mode Attack activate"));
}

void AWAKTestCharacter::NormalCatch()
{
	FGameplayAbilitySpec AbilitySpec(UWakGA_Catch::StaticClass());
	AbilitySpec.SourceObject = this;
	ASC->TryActivateAbility(ASC->GiveAbility(AbilitySpec));
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Try Normal Mode Catch activate"));
}


void AWAKTestCharacter::AsyncLoadWeapon(TSoftObjectPtr<UStaticMesh> WeaponData)
{
	if(WeaponData != nullptr)
	{
		Weapon->SetStaticMesh(WeaponData.Get());
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Weapon Data is Missing"));
	}
}

void AWAKTestCharacter::Experinment_HadokenAbility()
{
	FGameplayAbilitySpec AbilitySpec(UWakGA_RangedAttackTest::StaticClass());
	AbilitySpec.SourceObject = this;
	ASC->TryActivateAbility(ASC->GiveAbility(AbilitySpec));
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Try Experiment_Hadoken Ability Activate"));
}

 