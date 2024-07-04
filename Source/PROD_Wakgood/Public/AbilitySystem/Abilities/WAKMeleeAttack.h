// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WAKGA_Input.h"
#include "WAKMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWAKMeleeAttack : public UWAKGA_Input
{
	GENERATED_BODY()
	UWAKMeleeAttack();
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UAnimMontage* AttackMotionAnimMontage;
	void OnMontageComplete(UAnimMontage* Montage, bool bInterrupted);
	
};
