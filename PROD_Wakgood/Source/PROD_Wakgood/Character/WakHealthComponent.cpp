#include "WakHealthComponent.h"

// Unreal Header
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

// Wak Header
#include "AbilitySystem/Attributes/WakHealthSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(WakHealthComponent)


UWakHealthComponent::UWakHealthComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	AbilitySystemComponent = nullptr;
	HealthSet = nullptr;
	DeathState = EWakDeathState::NotDead;
}

void UWakHealthComponent::InitializeWithAbilitySystem(UAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (AbilitySystemComponent)
	{
		//UE_LOG(LogLyra, Error, TEXT("LyraHealthComponent: Health component for owner [%s] has already been initialized with an ability system."), *GetNameSafe(Owner));
		return;
	}

	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		//UE_LOG(LogLyra, Error, TEXT("LyraHealthComponent: Cannot initialize health component for owner [%s] with NULL ability system."), *GetNameSafe(Owner));
		return;
	}

	HealthSet = AbilitySystemComponent->GetSet<UWakHealthSet>();
	if (!HealthSet)
	{
		//UE_LOG(LogLyra, Error, TEXT("LyraHealthComponent: Cannot initialize health component for owner [%s] with NULL health set on the ability system."), *GetNameSafe(Owner));
		return;
	}

	// Register to listen for attribute changes.
// 	HealthSet->OnHealthChanged.AddUObject(this, &ThisClass::HandleHealthChanged);
// 	HealthSet->OnMaxHealthChanged.AddUObject(this, &ThisClass::HandleMaxHealthChanged);
// 	HealthSet->OnOutOfHealth.AddUObject(this, &ThisClass::HandleOutOfHealth);

	// TEMP: Reset attributes to default values.  Eventually this will be driven by a spread sheet.
	//AbilitySystemComponent->SetNumericAttributeBase(UWakHealthSet::GetHealthAttribute(), HealthSet->GetMaxHealth());

// 	ClearGameplayTags();
// 
// 	OnHealthChanged.Broadcast(this, HealthSet->GetHealth(), HealthSet->GetHealth(), nullptr);
// 	OnMaxHealthChanged.Broadcast(this, HealthSet->GetHealth(), HealthSet->GetHealth(), nullptr);
}

void UWakHealthComponent::UninitializeFromAbilitySystem()
{
}

float UWakHealthComponent::GetHealth() const
{
	return 0.0f;
}

float UWakHealthComponent::GetMaxHealth() const
{
	return 0.0f;
}

float UWakHealthComponent::GetHealthNormalized() const
{
	return 0.0f;
}

void UWakHealthComponent::StartDeath()
{
}

void UWakHealthComponent::FinishDeath()
{
}

void UWakHealthComponent::DamageSelfDestruct(bool bFellOutOfWorld)
{
}

void UWakHealthComponent::OnUnregister()
{
}

void UWakHealthComponent::ClearGameplayTags()
{
}

void UWakHealthComponent::HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
}

void UWakHealthComponent::HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
}

void UWakHealthComponent::HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
}

void UWakHealthComponent::OnRep_DeathState(EWakDeathState OldDeathState)
{
}
