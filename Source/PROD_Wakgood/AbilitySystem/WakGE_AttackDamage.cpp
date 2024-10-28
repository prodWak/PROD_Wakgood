// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WakGE_AttackDamage.h"

#include "AbilitySystem/WAKAttributeSet.h"
#include "AbilitySystem/MMC/MMC_Health.h"

UWakGE_AttackDamage::UWakGE_AttackDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	FGameplayModifierInfo HealthModifier;
	FCustomCalculationBasedFloat CustomCalculation;
	CustomCalculation.CalculationClassMagnitude = UMMC_Health::StaticClass();
	HealthModifier.Attribute = UWAKAttributeSet::GetHealthAttribute();
	HealthModifier.ModifierMagnitude = CustomCalculation;
	HealthModifier.ModifierOp = EGameplayModOp::Additive;
	Modifiers.Add(HealthModifier);

}
