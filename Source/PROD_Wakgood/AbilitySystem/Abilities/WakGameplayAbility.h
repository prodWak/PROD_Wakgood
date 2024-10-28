// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WakGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTagContainer InputTags;
};
