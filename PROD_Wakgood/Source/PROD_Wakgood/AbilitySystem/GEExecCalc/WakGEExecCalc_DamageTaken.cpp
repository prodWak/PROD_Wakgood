// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/WakGEExecCalc_DamageTaken.h"

#include "WakLogChannels.h"
#include "AbilitySystem/WakAttributeSet.h"

// capture attribute helper struct
struct FWakDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken);

	FWakDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWakAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWakAttributeSet, DamageTaken, Target, false);
	}
};

static const FWakDamageCapture& GetWakDamageCapture()
{
	static FWakDamageCapture Capture;
	return Capture;
}

UWakGEExecCalc_DamageTaken::UWakGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetWakDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetWakDamageCapture().DamageTakenDef);
}

void UWakGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWakDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	UE_LOG(LogWak, Warning, TEXT("SourceAttackPower : %f"), SourceAttackPower);
	
	if (SourceAttackPower > 0.f)
	{
		const FGameplayModifierEvaluatedData ModifierEvaluatedData(
			GetWakDamageCapture().DamageTakenProperty,
			EGameplayModOp::Override,
			SourceAttackPower
			);
		
		OutExecutionOutput.AddOutputModifier(ModifierEvaluatedData);
	}
}
