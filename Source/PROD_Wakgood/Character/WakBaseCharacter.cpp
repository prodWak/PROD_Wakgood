#include "WakBaseCharacter.h"
#include "AbilitySystemGlobals.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AWakBaseCharacter::AWakBaseCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	
	AttributeSet = CreateDefaultSubobject<UWakAttributeSet>(TEXT("AttributeSet"));

	PrimaryActorTick.bCanEverTick = true;
	bAbilitiesInitialized = false;
}

// Called when the game starts or when spawned
void AWakBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWakBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWakBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AWakBaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

float AWakBaseCharacter::GetHealth() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetHealth();
}

float AWakBaseCharacter::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

float AWakBaseCharacter::GetMana() const
{
	return AttributeSet->GetMana();
}

float AWakBaseCharacter::GetMaxMana() const
{
	return AttributeSet->GetMaxMana();
}

float AWakBaseCharacter::GetMoveSpeed() const
{
	return AttributeSet->GetMoveSpeed();
}

void AWakBaseCharacter::AddStartupGameplayAbilities()
{
	check(AbilitySystemComponent);

	if (GetLocalRole() == ROLE_Authority && !bAbilitiesInitialized)
	{
		// TODO: Add abilities
		bAbilitiesInitialized = true;
	}
}

void AWakBaseCharacter::RemoveStartupGameplayAbilities()
{
	check(AbilitySystemComponent);

	if (GetLocalRole() == ROLE_Authority && bAbilitiesInitialized)
	{
		// TODO: Remove abilities
		bAbilitiesInitialized = false;
	}
}

void AWakBaseCharacter::HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AWakBaseCharacter* InstigatorPawn, AActor* DamageCauser)
{
	OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorPawn, DamageCauser);
}

void AWakBaseCharacter::HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
	{
		OnHealthChanged(DeltaValue, EventTags);
	}
}

void AWakBaseCharacter::HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
	{
		OnManaChanged(DeltaValue, EventTags);
	}
}

void AWakBaseCharacter::HandleMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();

	if (bAbilitiesInitialized)
	{
		OnMoveSpeedChanged(DeltaValue, EventTags);
	}
}

