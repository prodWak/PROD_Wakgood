// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_Health.h"

#include "WAKTag.h"
#include "AbilitySystem/WAKAttributeSet.h"

UMMC_Health::UMMC_Health()
{

	SourceDamageDef.AttributeToCapture = UWAKAttributeSet::GetDamageAttribute();
	SourceDamageDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	SourceDamageDef.bSnapshot = false;
	TargetHealthDef.AttributeToCapture = UWAKAttributeSet::GetHealthAttribute();
	TargetHealthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	TargetHealthDef.bSnapshot = false;
	TargetResistDef.AttributeToCapture = UWAKAttributeSet::GetResistAttribute();
	TargetResistDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	TargetResistDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(SourceDamageDef);
	RelevantAttributesToCapture.Add(TargetHealthDef);
	RelevantAttributesToCapture.Add(TargetResistDef);

	Type_Normal = FWAKGameplayTags::Get().Character_Form_Normal; 
	Type_Water = FWAKGameplayTags::Get().Character_Type_Water; 
	Type_Iron = FWAKGameplayTags::Get().Character_Type_Iron; 
	Type_Light = FWAKGameplayTags::Get().Character_Type_Water; 
	Type_Wind = FWAKGameplayTags::Get().Character_Type_Wind; 
	
}

float UMMC_Health::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer SourceTags = GetSourceAggregatedTags(Spec);
	const FGameplayTagContainer TargetTags = GetTargetAggregatedTags(Spec);
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = &SourceTags;
	EvaluateParameters.TargetTags = &TargetTags;
	float Damage = 0.f;
	GetCapturedAttributeMagnitude(SourceDamageDef,Spec,EvaluateParameters,Damage);

	float TestDamage = 1.f;
	float Health = 0.f;
	GetCapturedAttributeMagnitude(TargetHealthDef,Spec,EvaluateParameters,Health);
	float Resist = 0.f;
	GetCapturedAttributeMagnitude(TargetResistDef,Spec,EvaluateParameters,Resist);
	float EffectivenessMultiply = GetTypeEffectivenessMultiplier(EvaluateParameters.SourceTags,EvaluateParameters.TargetTags);
	//현재체력 - (기본 데미지 + (기본 데미지 * 상성 배율) - ((저항력) * 상성 배율)
	//float EvaluateDamage = Health - (Damage + (Damage * EffectivenessMultiply) - (Resist * EffectivenessMultiply));
	float EvaluateDamage = Health - (TestDamage + (TestDamage * EffectivenessMultiply) - (Resist * EffectivenessMultiply));
	
	FString Test1 = FString::Printf(TEXT("EffectivnessMultiply Is : %f"),EffectivenessMultiply);
	FString Test2 = FString::Printf(TEXT("Evaluate Damage Is : %f"),FMath::Clamp(EvaluateDamage,0.1f,1.0f));
	GEngine->AddOnScreenDebugMessage(1,5.f,FColor::Red,Test1);
	GEngine->AddOnScreenDebugMessage(2,5.f,FColor::Red,Test2);
	
	return FMath::Clamp(10,0.1f,1.0f) * -1.f; //이 값만큼 체력을 다운 시킴.
}

float UMMC_Health::GetTypeEffectivenessMultiplier(const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags) const
{
	if(SourceTags->HasTag(Type_Normal))
	{
		if(TargetTags->HasTag(Type_Normal))
		{
			return 1.f;
		}
		else
		{
			return 0.5f;
		}
	}
	else if(SourceTags->HasTag(Type_Water))
	{
		if(TargetTags->HasTag(Type_Normal))
		{
			return 1.5f;
		}
		else if(TargetTags->HasTag(Type_Light))
		{
			return 1.5f;
		}
		else if(TargetTags->HasTag(Type_Wind))
		{
			return 0.5f;
		}
		else
		{
			return 1.f;
		}

	}
	else if(SourceTags->HasTag(Type_Iron))
	{
		if(TargetTags->HasTag(Type_Normal))
		{
			return 1.5f;
		}
		else if(TargetTags->HasTag(Type_Light))
		{
			return 0.5f;
		}
		else if(TargetTags->HasTag(Type_Wind))
		{
			return 1.5f;
		}
		else
		{
			return 1.f;	
		}

	}
	else if(SourceTags->HasTag(Type_Light))
	{
		if(TargetTags->HasTag(Type_Normal))
		{
			return 1.5f;
		}
		else if(TargetTags->HasTag(Type_Water))
		{
			return 0.5f;
		}
		else if(TargetTags->HasTag(Type_Iron))
		{
			return 1.5f;
		}
		else
		{
			return 1.f;	
		}

	}
	else if(SourceTags->HasTag(Type_Wind))
	{
		if(TargetTags->HasTag(Type_Normal))
		{
			return 1.5f;
		}
		else if(TargetTags->HasTag(Type_Water))
		{
			return 1.5f;
		}
		else if(TargetTags->HasTag(Type_Iron))
		{
			return 0.5f;
		}
		else
		{
			return 1.f;	
		}

	}
	else
	{
		return 1.f;
	}
}
