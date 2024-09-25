#include "WakCharacterBase.h"

// Wak Header
#include "Character/WakHealthComponent.h"

// Unreal Header
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AWakCharacterBase::AWakCharacterBase(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	HealthComponent = CreateDefaultSubobject<UWakHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeathStarted.AddDynamic(this, &ThisClass::OnDeathStarted);
	HealthComponent->OnDeathFinished.AddDynamic(this, &ThisClass::OnDeathFinished);

}

void AWakCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AWakCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AWakCharacterBase::OnDeathStarted(AActor* OwningActor)
{
	DisableMovementAndCollision();
}

void AWakCharacterBase::OnDeathFinished(AActor* OwningActor)
{
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::DestroyDueToDeath);
}

void AWakCharacterBase::DisableMovementAndCollision()
{
	if (Controller)
	{
		Controller->SetIgnoreMoveInput(true);
	}

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
}

void AWakCharacterBase::DestroyDueToDeath()
{
	K2_OnDeathFinished();

	UninitAndDestroy();
}

void AWakCharacterBase::UninitAndDestroy()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		DetachFromControllerPendingDestroy();
		SetLifeSpan(0.1f);
	}

	// Uninitialize the ASC if we're still the avatar actor (otherwise another pawn already did it when they became the avatar actor)
	if (UAbilitySystemComponent* WakASC = GetAbilitySystemComponent())
	{
		if (WakASC->GetAvatarActor() == this)
		{
			/*PawnExtComponent->UninitializeAbilitySystem();*/
		}
	}

	SetActorHiddenInGame(true);
}


