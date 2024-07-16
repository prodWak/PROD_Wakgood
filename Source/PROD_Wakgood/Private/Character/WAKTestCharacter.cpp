// Copyright Epic Games, Inc. All Rights Reserved.

#include "..\..\Public\Character\WAKTestCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "..\..\Public\AbilitySystem\WAKASC.h"
#include "..\..\Public\AbilitySystem\WAKAttributeSet.h"
#include "..\..\Public\WAKDataTableData.h"
#include "..\..\Public\WAKInputComponent.h"
#include "..\..\Public\WAKTag.h"
#include "Engine/DataTable.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "AbilitySystemBlueprintLibrary.h"

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

	/*
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh());
	Weapon->SetGenerateOverlapEvents(false);
	Weapon->OnComponentBeginOverlap.AddDynamic(this,&AWAKTestCharacter::OnWeaponBeginOverlap);
	*/
	//Weapon->SetStaticMesh("");
	
	/*static ConstructorHelpers::FObjectFinder<UDataTable> ObjectFinder(TEXT("/Script/Engine.DataTable/Game/DataTable/DT_WeaponData.DT_WeaponData"));
	if(ObjectFinder.Succeeded())
	{
		WeaponMeshDataTable = ObjectFinder.Object;
	}*/
	CharacterType = FWAKGameplayTags::Get().Character_Type_Normal;
}

void AWAKTestCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	//ASC->OnFormChange.AddUObject(this,&AWAKTestCharacter::AbilityActivateByTag);
	//ASC->OnFormChange.AddUObject(this,&AWAKTestCharacter::ChangeWeaponByTag);
	
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

UAbilitySystemComponent* AWAKTestCharacter::GetAbilitySystemComponent() const
{
	return ASC; 
}


void AWAKTestCharacter::SetWeaponOverlap(bool CanOverlap)
{
	Weapon->SetGenerateOverlapEvents(CanOverlap);
}

void AWAKTestCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ASC->InitAbilityActorInfo(this,this);
	ASC->AddLooseGameplayTag(FWAKGameplayTags::Get().Character_Form_Normal);
	ASC->CurrentFormTag = FWAKGameplayTags::Get().Character_Form_Normal;
	InitializeAttributeToEffect();
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
	ApplyEffectToSelf(PrimaryEffect,1.f);
}



void AWAKTestCharacter::AbilityInputTagPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Red,*InputTag.ToString());
	ASC->AbilityInputTagPressed(InputTag);
	TArray<FGameplayAbilitySpec> AbilitySpecs = ASC->GetActivatableAbilities();
	for(FGameplayAbilitySpec AbilitySpec : AbilitySpecs)
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(FWAKGameplayTags::Get().InputTag_Q))
		{
			ASC->AbilitySpecInputPressed(AbilitySpec); 
		}
	}
}

void AWAKTestCharacter::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != this)
	{
		ApplyEffectToTarget(OtherActor,DamageEffect);
	}
}

// void AWAKTestCharacter::AbilityActivateByTag()
// {
// 	FWAKGameplayTags GameplayTags = FWAKGameplayTags::Get();
// 	FGameplayTag Tag = ASC->CurrentFormTag;
// 	UE_LOG(LogTemp,Warning,TEXT("Current Tag is %s"),*Tag.ToString());
// 	if(ASC->HasMatchingGameplayTag(GameplayTags.Character_Form_Normal))
// 	{
// 		ASC->GiveAttackAbility(ASC->NormalAttackAbility);
// 	}
// 	else if (ASC->HasMatchingGameplayTag(GameplayTags.Character_Form_Melee))
// 	{
// 		ASC->GiveAttackAbility(ASC->MeleeAttackAbility);
// 	}
// 	else if (ASC->HasMatchingGameplayTag(GameplayTags.Character_Form_Range))
// 	{
// 		ASC->GiveAttackAbility(ASC->RangeAttackAbility);
// 	}
// 	else if (ASC->HasMatchingGameplayTag(GameplayTags.Character_Form_LongRange))
// 	{
// 		ASC->GiveAttackAbility(ASC->LongRangeAttackAbility);
// 	}
// 	
// }

void AWAKTestCharacter::ChangeWeaponByTag()
{
	FWAKGameplayTags GameplayTags = FWAKGameplayTags::Get();
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	FGameplayTag Tag = ASC->CurrentFormTag;
	
	check(WeaponMeshDataTable);
	if(Tag.GetTagName() == GameplayTags.Character_Form_Normal.GetTagName())
	{
		TSoftObjectPtr<UStaticMesh> WeaponData = WeaponMeshDataTable->FindRow<FWeaponDT>(FName("NormalForm"),TEXT("Get NormalForm Failed"))->WeaponMesh;
		Streamable.RequestAsyncLoad(WeaponData.ToSoftObjectPath(),FStreamableDelegate::CreateUObject(this,&AWAKTestCharacter::AsyncLoadWeapon,WeaponData));
	}
	else if (Tag == GameplayTags.Character_Form_Melee)
	{
		TSoftObjectPtr<UStaticMesh> WeaponData = WeaponMeshDataTable->FindRow<FWeaponDT>(FName("MeleeForm"),TEXT("Get MeleeFormForm Failed"))->WeaponMesh;
		Streamable.RequestAsyncLoad(WeaponData.ToSoftObjectPath(),FStreamableDelegate::CreateUObject(this,&AWAKTestCharacter::AsyncLoadWeapon,WeaponData));
	}
	else if (Tag == GameplayTags.Character_Form_Range)
	{
		TSoftObjectPtr<UStaticMesh> WeaponData = WeaponMeshDataTable->FindRow<FWeaponDT>(FName("RangeForm"),TEXT("Get RangeForm Failed"))->WeaponMesh;
		Streamable.RequestAsyncLoad(WeaponData.ToSoftObjectPath(),FStreamableDelegate::CreateUObject(this,&AWAKTestCharacter::AsyncLoadWeapon,WeaponData));
	}
	else if (Tag == GameplayTags.Character_Form_LongRange)
	{
		TSoftObjectPtr<UStaticMesh> WeaponData = WeaponMeshDataTable->FindRow<FWeaponDT>(FName("LongRangeForm"),TEXT("Get LongRangeForm Failed"))->WeaponMesh;
		Streamable.RequestAsyncLoad(WeaponData.ToSoftObjectPath(),FStreamableDelegate::CreateUObject(this,&AWAKTestCharacter::AsyncLoadWeapon,WeaponData));
	}
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

//////////////////////////////////////////////////////////////////////////
// Input

void AWAKTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UWAKInputComponent* EnhancedInputComponent = Cast<UWAKInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWAKTestCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWAKTestCharacter::Look);

		check(InputConfig);
		EnhancedInputComponent->BindAbilityActions(InputConfig,this,&AWAKTestCharacter::AbilityInputTagPressed);
		//기술 전부 AWAKTestCharacter::AbilityInputTagPressed 이 함수에 바인딩함 
	}
}

void AWAKTestCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWAKTestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
 