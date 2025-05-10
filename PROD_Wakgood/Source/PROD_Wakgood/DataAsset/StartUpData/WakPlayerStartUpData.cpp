// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUpData/WakPlayerStartUpData.h"

#include "AbilitySystem/WakAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WakGameplayAbility.h"

bool FWakPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

void UWakPlayerStartUpData::GiveToAbilitySystemComponent(UWakAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (WakPlayerStartUpAbilitySets.IsEmpty())
	{
		return;
	}

	for (const FWakPlayerAbilitySet& AbilitySet : WakPlayerStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
