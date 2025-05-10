// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WakEnemyGameplayAbility.h"

#include "Character/Enemy/WakEnemyCharacter.h"

AWakEnemyCharacter* UWakEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedWakEnemyCharacter.IsValid())
	{
		CachedWakEnemyCharacter = Cast<AWakEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	
	return CachedWakEnemyCharacter.IsValid() ? CachedWakEnemyCharacter.Get() : nullptr;
}

UWakEnemyCombatComponent* UWakEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
