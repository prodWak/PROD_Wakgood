// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WakGameplayAbilityEnemy.h"

#include "Character/Enemy/WakEnemyCharacter.h"

AWakEnemyCharacter* UWakGameplayAbilityEnemy::GetEnemyCharacterFromActorInfo()
{
	if (!CachedWakEnemyCharacter.IsValid())
	{
		CachedWakEnemyCharacter = Cast<AWakEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	
	return CachedWakEnemyCharacter.IsValid() ? CachedWakEnemyCharacter.Get() : nullptr;
}

UWakEnemyCombatComponent* UWakGameplayAbilityEnemy::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
