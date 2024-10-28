// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WakDamageGameplayAbility.h"
#include "Actor/WakProjectile.h"
#include "WakProjectileSpell.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakProjectileSpell : public UWakDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void SpawnProjectile(const FVector ProjectileTargetLocation);

	UPROPERTY()
	FScalableFloat Damage;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWakProjectile> ProjectileClass;
};
