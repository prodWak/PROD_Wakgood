// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WakGameplayAbilityBase.generated.h"

class UWakAbilitySystemComponent;
class UWakPawnCombatComponent;

/** 시작 시 활성화되는 어빌리티와 입력 시 활성화 되는 어빌리티 구분 */
UENUM(BlueprintType)
enum class EWakAbilityActivationPolicy : uint8
{
	OnTriggered UMETA(DisplayName = "Triggered"),
	OnGiven		UMETA(DisplayName = "Given")
};

UENUM(BlueprintType)
enum class EWarriorSuccessType : uint8
{
	Successful,
	Failed
};

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "Wak|Abilities")
	EWakAbilityActivationPolicy AbilityActivationPolicy = EWakAbilityActivationPolicy::OnTriggered;
	
	UFUNCTION(BlueprintPure, Category = "Wak|Ability")
	UWakPawnCombatComponent* GetWakPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Wak|Ability")
	UWakAbilitySystemComponent* GetWakAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle) const;

	UFUNCTION(BlueprintCallable, Category = "Wak|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EWarriorSuccessType& OutSuccessType);
};
