// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "WakAbilityTypes.h"
#include "WAKTag.h"
#include "AbilitySystem/WakAbilitySystemLibrary.h"
#include "AbilitySystem/WAKAttributeSet.h"

struct WakDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resist); //속성 캡쳐 매크로 1 ResistDef,ResistProperty 생성

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	WakDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWAKAttributeSet, Resist, Target, false); //속성 캡쳐 매크로 2 Target에게서 속성 캡쳐, Snapshot은 false
		//TagsToCaptureDefs.Add(FWAKGameplayTags::Get().속성,속성Def) //태그와 속성 연결
	}
};
static const WakDamageStatics& DamageStatic()
{
	static WakDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatic().ResistDef);
	//FGameplayEffectAttributeCaptureDefinition
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	//Get Damage Set By Caller Magnitude
	float Damage = Spec.GetSetByCallerMagnitude(FWAKGameplayTags::Get().Damage); //태그와 함께 Magnitude 설정 - 태그를 이용해 불러오기
	for(auto& pair : FWAKGameplayTags::Get().DamageTypesToResistances)
	{
		FGameplayTag DamageTypeTag = pair.Key;
		FGameplayTag ResistanceTag = pair.Value;
		checkf(WakDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag),TEXT("TagsToCapture doesn't contain Tag: [%s] in ExacCalc_Damage"), *ResistanceTag.ToString());
		FGameplayEffectAttributeCaptureDefinition CaptureDef = WakDamageStatics().TagsToCaptureDefs[ResistanceTag];
		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef,EvaluateParameters,Resistance);
		Resistance = FMath::Clamp(Resistance,0.f,100.f);
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(pair.Key);
		DamageTypeValue *= (DamageTypeValue - Resistance) / 100;
		Damage += DamageTypeValue;
	}
	float Resist = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().ResistDef,EvaluateParameters,Resist); //Resist 변수에 ResistDef값을 담는 듯.

	float Effectiveness = GetEffectivenessMultiplier(SourceTags,TargetTags);
	Damage = (Damage + (Damage * Effectiveness)) - (Resist * Effectiveness);

	/*
	if(TargetTags->HasTag(FWAKGameplayTags::Get().Action_IsBlocking))
	{
		Damage *= 0.25f;
	}
	*/

	const FGameplayModifierEvaluatedData EvaluatedData(UWAKAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive, Damage); //Resiste값을 기존 Resist에 더함.
	OutExecutionOutput.AddOutputModifier(EvaluatedData); // 평가한 데이터를 밖으로 내보내기

}

float UExecCalc_Damage::GetEffectivenessMultiplier(const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags) const
{
	FWAKGameplayTags GameplayTags = FWAKGameplayTags::Get();
	if(SourceTags->HasTag(GameplayTags.Character_Type_Normal))
	{
		if(TargetTags->HasTag(GameplayTags.Character_Type_Normal))
		{
			return 1.f;
		}
			return 0.5f;
	}
	if(SourceTags->HasTag(GameplayTags.Character_Type_Water))
	{
		if(TargetTags->HasTag(GameplayTags.Character_Type_Normal))
		{
			return 1.5f;
		}
		if(TargetTags->HasTag(GameplayTags.Character_Type_Light))
		{
			return 1.5f;
		}
		if(TargetTags->HasTag(GameplayTags.Character_Type_Wind))
		{
			return 0.5f;
		}
			return 1.f;
	}
	if(SourceTags->HasTag(GameplayTags.Character_Type_Iron))
	{
		if(TargetTags->HasTag(GameplayTags.Character_Type_Normal))
		{
			return 1.5f;
		}
		if(TargetTags->HasTag(GameplayTags.Character_Type_Light))
		{
			return 0.5f;
		}
		if(TargetTags->HasTag(GameplayTags.Character_Type_Wind))
		{
			return 1.5f;
		}
		return 1.f;	

	}
	if(SourceTags->HasTag(GameplayTags.Character_Type_Light))
	{
		if(TargetTags->HasTag(GameplayTags.Character_Type_Normal))
		{
			return 1.5f;
		}
		if(TargetTags->HasTag(GameplayTags.Character_Type_Water))
		{
			return 0.5f;
		}
		if(TargetTags->HasTag(GameplayTags.Character_Type_Iron))
		{
			return 1.5f;
		}
		return 1.f;	

	}
	if(SourceTags->HasTag(GameplayTags.Character_Type_Wind))
	{
		if(TargetTags->HasTag(GameplayTags.Character_Type_Normal))
		{
			return 1.5f;
		}
		if(TargetTags->HasTag(GameplayTags.Character_Type_Water))
		{
			return 1.5f;
		}
		if(TargetTags->HasTag(GameplayTags.Character_Type_Iron))
		{
			return 0.5f;
		}
		return 1.f;	
	}
		return 1.f;
}
