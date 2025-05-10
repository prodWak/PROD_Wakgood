// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUpData/WakEnemyStartUpData.h"

// WakHeader
#include "AbilitySystem/WakAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WakEnemyGameplayAbility.h"

void UWakEnemyStartUpData::GiveToAbilitySystemComponent(UWakAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (EnemyCombatAbilities.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UWakEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
	{
		if (!AbilityClass)
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilityClass);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
