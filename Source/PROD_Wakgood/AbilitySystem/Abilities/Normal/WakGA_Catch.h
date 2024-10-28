// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WakGA_AttackBase.h"
#include "WakGA_Catch.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakGA_Catch : public UWakGA_AttackBase
{
	GENERATED_BODY()
	UWakGA_Catch();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	
	
	UAnimMontage* CatchAttackAnim;

public:
	UFUNCTION()
	void AbsorbEnemy(FGameplayEventData Payload);
	UFUNCTION()
	void ChangeFormByEnemyTag(AWAKTestCharacter* Target);
	

	
};
