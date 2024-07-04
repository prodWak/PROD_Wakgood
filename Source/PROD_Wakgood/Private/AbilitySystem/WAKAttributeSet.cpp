// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\AbilitySystem\WAKAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"

UWAKAttributeSet::UWAKAttributeSet()
{
	InitHealth(3.f);
	InitMaxHealth(3.f);
}
void UWAKAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0,GetMaxHealth()));
	}
	
}

void UWAKAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0, GetMaxHealth());
	}
}
