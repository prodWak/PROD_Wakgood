// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUpData/WakStartUpDataBase.h"

#include "AbilitySystem/WakAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WakGameplayAbility.h"

void UWakStartUpDataBase::GiveToAbilitySystemComponent(UWakAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UWakStartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UWakGameplayAbility>>& InAbilitiesToGive,
	UWakAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UWakGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability)
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
