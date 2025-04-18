// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WakPlayerGameplayAbility.h"

#include "Character/WakGood/WakWakGoodCharacter.h"
#include "Controller/WakPlayerController.h"

AWakWakGoodCharacter* UWakPlayerGameplayAbility::GetWakPlayerCharacterFromActorInfo()
{
	if (!CachedWakPlayerCharacter.IsValid())
	{
		CachedWakPlayerCharacter = Cast<AWakWakGoodCharacter>(CurrentActorInfo->AvatarActor);
	}
	
	return CachedWakPlayerCharacter.IsValid() ? CachedWakPlayerCharacter.Get() : nullptr;
}

AWakPlayerController* UWakPlayerGameplayAbility::GetWakPlayerControllerFromActorInfo()
{
	if (!CachedWakPlayerController.IsValid())
	{
		CachedWakPlayerController = Cast<AWakPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedWakPlayerController.IsValid() ? CachedWakPlayerController.Get() : nullptr;
}

UWakPlayerCombatComponent* UWakPlayerGameplayAbility::GetWakPlayerCombatComponentFromActorInfo()
{
	return GetWakPlayerCharacterFromActorInfo()->GetWakPlayerCombatComponent();
}
