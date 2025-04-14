// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WakGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EWakAbilityActivationPolicy : uint8
{
	OnTriggered UMETA(DisplayName = "Triggered"),
	OnGiven		UMETA(DisplayName = "Given")
};

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Wak|Abilities")
	EWakAbilityActivationPolicy AbilityActivationPolicy = EWakAbilityActivationPolicy::OnTriggered;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
