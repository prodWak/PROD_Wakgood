// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WakGA_AttackBase.h"
#include "Abilities/GameplayAbility.h"
#include "WakGA_RangedAttackBase.generated.h"

class AWakProjectile;
/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakGA_RangedAttackBase : public UWakGA_AttackBase
{
	GENERATED_BODY()
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
public:
	UFUNCTION()
	void SpawnProjectile(FGameplayEventData Payload);
	UFUNCTION()
	void SetProjectile(TSubclassOf<AWakProjectile> ProjectileClass);

	TSubclassOf<AWakProjectile> AbilityProjectileClass;

	AWakProjectile* Projectile;
};


