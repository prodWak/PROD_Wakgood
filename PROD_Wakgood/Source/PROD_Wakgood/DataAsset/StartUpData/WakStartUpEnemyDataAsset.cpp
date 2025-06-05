// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUpData/WakStartUpEnemyDataAsset.h"

// WakHeader
#include "AbilitySystem/WakAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WakGameplayAbilityEnemy.h"

void UWakStartUpEnemyDataAsset::GiveToAbilitySystemComponent(UWakAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (EnemyCombatAbilities.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UWakGameplayAbilityEnemy>& AbilityClass : EnemyCombatAbilities)
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
