// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WakAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(FGameplayTag& InInputTag);
	void OnAbilityInputReleased(FGameplayTag& InInputTag);
};
