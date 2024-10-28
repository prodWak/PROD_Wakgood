// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WAKGA_FormChangeBase.h"
#include "WAKGA_FormChangeNormal.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWAKGA_FormChangeNormal : public UWAKGA_FormChangeBase
{
	GENERATED_BODY()
	UWAKGA_FormChangeNormal();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
