// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WakPlayerCharacter.h"

#include "Input/WAKInputComponent.h"
#include "AbilitySystem/WAKASC.h"
#include "AbilitySystem/WAKAttributeSet.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/WakPlayerState.h"
#include "Character/WakEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AWakPlayerCharacter::AWakPlayerCharacter()
{
	Shiled = CreateDefaultSubobject<UBoxComponent>(TEXT("Shiled"));
	Shiled->SetActive(false);
	Shiled->SetupAttachment(RootComponent);
	Shiled->SetCollisionProfileName("OverlapAllDynamic");
	GetCharacterMovement()->RotationRate = FRotator(0,10000.f,0);
	
}

void AWakPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp,Warning,TEXT("Current Health : %f"),GetAttributeSet()->GetHealth());
	GetAbilitySystemComponent()->RegisterGameplayTagEvent(FWAKGameplayTags::Get().Effects_HitReact).AddUObject(this,&AWakPlayerCharacter::HitReact);
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GetAttributeSet()->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData)
	{
		UE_LOG(LogTemp,Warning,TEXT("Remain Health : %f"),GetAttributeSet()->GetHealth());
	});
}

void AWakPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ASC = Cast<AWakPlayerState>(GetPlayerState())->GetAbilitySystemComponent();
	ASC->InitAbilityActorInfo(GetPlayerState(),this);
	AttributeSet = GetPlayerState<AWakPlayerState>()->GetAttributeSet();

	ASC->AddLooseGameplayTag(FWAKGameplayTags::Get().Character_Form_Normal);
	Cast<UWAKASC>(ASC)->CurrentFormTag = FWAKGameplayTags::Get().Character_Form_Normal;

	InitializeAttributeToEffect();
}

void AWakPlayerCharacter::Die()
{
	SetLifeSpan(Lifespan);
	Super::Die();
}

void AWakPlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	UE_LOG(LogTemp,Warning,TEXT("Is Landed"));
	SetPlatformCollisionResponseBlock();
}

void AWakPlayerCharacter::HitReact(FGameplayTag Tag, int32 NewCount)
{
	if(NewCount >= 1)
	{
		PlayAnimMontage(HitReactMontage);
		GetCharacterMovement()->StopActiveMovement();
		//무적으로 만드는 기능, 맞은 방향에서 살짝 뒤로 이동시키기
		//LaunchCharacter(GetActorForwardVector() * -1.f * KnockBackDistance,true,false);
		GetLocalViewingPlayerController()->DisableInput(GetLocalViewingPlayerController());
		
	}
	else if(NewCount <= 0)
	{
		StopAnimMontage(HitReactMontage);
		GetLocalViewingPlayerController()->EnableInput(GetLocalViewingPlayerController());
	}
}

void AWakPlayerCharacter::SetPlatformCollisionResponseBlock()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Block);
}

void AWakPlayerCharacter::SetPlatformCollisionResponseIgnore()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Ignore);
}

void AWakPlayerCharacter::MoveUnderPlatform()
{
	if(bAbleDown)
	{
		OnMoveUnderPlatform.Broadcast();
	}
}

void AWakPlayerCharacter::NormalAttack()
{
	//1번안 : 채찍에 Overlap된 액터를 가져와서 해당 액터에게 Ability에서 Effect 적용시키기.
	//2번안 : 어빌리티에서 채찍의 gameplayeffect를 설정해서 닿으면 채찍 Actor에서 상대에게 Effect 적용 시키기.
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(FWAKGameplayTags::Get().Ability_Normal_Attack.GetSingleTagContainer());
}

void AWakPlayerCharacter::NormalGrab()
{
	//채찍에 Overlap된 액터가 가지고 있는 태그를 이용해서 Ability 발동 (ActivateAbilityByTag(EnemyTag) 이런식으로 + 적은 강제로 체력을 0으로 만듬.
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(FWAKGameplayTags::Get().Ability_Normal_Grab.GetSingleTagContainer());
}

void AWakPlayerCharacter::ReturnFormNormal()
{
	//가지고 있던 Ability들을 모두 지우고 Normal, Common Ability들을 적용.
	GetAbilitySystemComponent()->TryActivateAbilitiesByTag(FWAKGameplayTags::Get().Ability_FormChange_Normal.GetSingleTagContainer());
}


