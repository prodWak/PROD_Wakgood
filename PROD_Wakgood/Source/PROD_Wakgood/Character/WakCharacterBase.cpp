#include "WakCharacterBase.h"

// Wak Header
// #include "Components/Health/WakHealthComponent.h"
#include "AbilitySystem/WakAbilitySystemComponent.h"
#include "AbilitySystem/WakAttributeSet.h"

// Unreal Header
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AWakCharacterBase::AWakCharacterBase(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	// Configure character movement
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->JumpZVelocity = 700.f;
		MovementComponent->AirControl = 0.35f;
		MovementComponent->MaxWalkSpeed = 500.f;
		MovementComponent->bConstrainToPlane = true;
		MovementComponent->SetPlaneConstraintNormal(FVector(1.f, 0.f, 0.f));
	}

	WakAbilitySystemComponent = CreateDefaultSubobject<UWakAbilitySystemComponent>(TEXT("WakAbilitySystemComponent"));
	
	WakAttribute = CreateDefaultSubobject<UWakAttributeSet>(TEXT("WakAttributeSet"));

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
}

void AWakCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWakCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (WakAbilitySystemComponent)
	{
		WakAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to [ %s ]"), *GetNameSafe(this));
	}
}

UAbilitySystemComponent* AWakCharacterBase::GetAbilitySystemComponent() const
{
	return GetWakAbilitySystemComponent();
}

UWakPawnCombatComponent* AWakCharacterBase::GetWakPawnCombatComponent()
{
	return nullptr;
}
