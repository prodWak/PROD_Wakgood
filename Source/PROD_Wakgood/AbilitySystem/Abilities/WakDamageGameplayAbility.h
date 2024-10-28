// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WakGameplayAbility.h"
#include "WakDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakDamageGameplayAbility : public UWakGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
	
};
