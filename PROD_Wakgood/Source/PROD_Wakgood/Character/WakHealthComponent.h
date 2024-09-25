#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "WakHealthComponent.generated.h"

class ULyraHealthComponent;

class UAbilitySystemComponent;
class UWakHealthSet;

struct FGameplayEffectSpec;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWakHealth_DeathEvent, AActor*, OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FWakHealth_AttributeChanged, UWakHealthComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);

UENUM(BlueprintType)
enum class EWakDeathState : uint8
{
	NotDead = 0,
	DeathStarted,
	DeathFinished
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROD_WAKGOOD_API UWakHealthComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:	
	UWakHealthComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Wak|Health")
	void InitializeWithAbilitySystem(UAbilitySystemComponent* InASC);

	// Uninitialize the component, clearing any references to the ability system.
	UFUNCTION(BlueprintCallable, Category = "Wak|Health")
	void UninitializeFromAbilitySystem();

	// Returns the current health value.
	UFUNCTION(BlueprintCallable, Category = "Wak|Health")
	float GetHealth() const;

	// Returns the current maximum health value.
	UFUNCTION(BlueprintCallable, Category = "Wak|Health")
	float GetMaxHealth() const;

	// Returns the current health in the range [0.0, 1.0].
	UFUNCTION(BlueprintCallable, Category = "Wak|Health")
	float GetHealthNormalized() const;

	UFUNCTION(BlueprintCallable, Category = "Wak|Health")
	EWakDeathState GetDeathState() const { return DeathState; }

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Wak|Health", Meta = (ExpandBoolAsExecs = "ReturnValue"))
	bool IsDeadOrDying() const { return (DeathState > EWakDeathState::NotDead); }

	// Begins the death sequence for the owner.
	virtual void StartDeath();

	// Ends the death sequence for the owner.
	virtual void FinishDeath();

	// Applies enough damage to kill the owner.
	virtual void DamageSelfDestruct(bool bFellOutOfWorld = false);

public:

	// Delegate fired when the health value has changed. This is called on the client but the instigator may not be valid
	UPROPERTY(BlueprintAssignable)
	FWakHealth_AttributeChanged OnHealthChanged;

	// Delegate fired when the max health value has changed. This is called on the client but the instigator may not be valid
	UPROPERTY(BlueprintAssignable)
	FWakHealth_AttributeChanged OnMaxHealthChanged;

	// Delegate fired when the death sequence has started.
	UPROPERTY(BlueprintAssignable)
	FWakHealth_DeathEvent OnDeathStarted;

	// Delegate fired when the death sequence has finished.
	UPROPERTY(BlueprintAssignable)
	FWakHealth_DeathEvent OnDeathFinished;

protected:
	virtual void OnUnregister() override;

	void ClearGameplayTags();

	virtual void HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	virtual void HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	virtual void HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);

	UFUNCTION()
	virtual void OnRep_DeathState(EWakDeathState OldDeathState);

protected:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<const UWakHealthSet> HealthSet;

	UPROPERTY()
	EWakDeathState DeathState;
};
