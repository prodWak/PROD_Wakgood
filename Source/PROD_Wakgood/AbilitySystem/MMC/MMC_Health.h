// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_Health.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UMMC_Health : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	UMMC_Health();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	float GetTypeEffectivenessMultiplier(const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags) const;
	//현재체력 - (기본 데미지 + (기본 데미지 * 1.5(상성 적용시)) - ((저항력) ** (1.5(상성 적용시)))


	FGameplayEffectAttributeCaptureDefinition TargetHealthDef;
	FGameplayEffectAttributeCaptureDefinition SourceDamageDef;
	FGameplayEffectAttributeCaptureDefinition TargetResistDef;

	FGameplayTag Type_Normal;
	FGameplayTag Type_Water;
	FGameplayTag Type_Iron;
	FGameplayTag Type_Light;
	FGameplayTag Type_Wind;
	
};
