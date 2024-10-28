// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WakGA_RangedAttackBase.h"
#include "WakGA_RangedAttackTest.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakGA_RangedAttackTest : public UWakGA_RangedAttackBase
{
	GENERATED_BODY()
	UWakGA_RangedAttackTest();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UAbilityTask_WaitGameplayEvent* FireEvent;
	UAbilityTask_WaitGameplayEvent* AttackEvent;
	UAnimMontage* TestAnimMontage;
};
