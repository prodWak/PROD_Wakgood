// Fill out your copyright notice in the Description page of Project Settings.


#include "WakPlayerState.h"
#include "AbilitySystem/WAKASC.h"
#include "AbilitySystem/WAKAttributeSet.h"


AWakPlayerState::AWakPlayerState()
{
	ASC = CreateDefaultSubobject<UWAKASC>("ASC");
	AttributeSet = CreateDefaultSubobject<UWAKAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AWakPlayerState::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(ASC);
}
