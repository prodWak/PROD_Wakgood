// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WakPlayerCharacter.h"

#include "Input/WAKInputComponent.h"
#include "AbilitySystem/WAKASC.h"
#include "AbilitySystem/WAKAttributeSet.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/WakPlayerState.h"

AWakPlayerCharacter::AWakPlayerCharacter()
{
	Shiled = CreateDefaultSubobject<UBoxComponent>(TEXT("Shiled"));
	Shiled->SetActive(false);
	Shiled->SetupAttachment(RootComponent);
	Shiled->SetCollisionProfileName("OverlapAllDynamic");

{}	
}

void AWakPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp,Warning,TEXT("Current Health : %f"),GetAttributeSet()->GetHealth());
	
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



