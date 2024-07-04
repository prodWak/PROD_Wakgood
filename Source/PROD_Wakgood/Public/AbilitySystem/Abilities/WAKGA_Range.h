// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

 #include "CoreMinimal.h"
#include "WAKGA.h"
#include "WAKGA_Range.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWAKGA_Range : public UWAKGA
{
	GENERATED_BODY()
	UWAKGA_Range();
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};
