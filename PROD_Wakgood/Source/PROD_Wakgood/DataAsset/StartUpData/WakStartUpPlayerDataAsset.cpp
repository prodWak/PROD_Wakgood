// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUpData/WakStartUpPlayerDataAsset.h"

#include "AbilitySystem/WakAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WakGameplayAbilityBase.h"

bool FWakPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

void UWakStartUpPlayerDataAsset::GiveToAbilitySystemComponent(UWakAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
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
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
