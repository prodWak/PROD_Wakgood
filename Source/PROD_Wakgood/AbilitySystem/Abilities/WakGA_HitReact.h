// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WakGA_HitReact.generated.h"
class UAbilityTask_PlayMontageAndWait; 
/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakGA_HitReact : public UGameplayAbility
{
	GENERATED_BODY()
	UWakGA_HitReact();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UGameplayEffect* HitReactEffect;
	UFUNCTION()
	void OnMontageEnded();
	UPROPERTY()
	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait;
	UPROPERTY()
	FActiveGameplayEffectHandle ActiveEffectHitReact;
};
