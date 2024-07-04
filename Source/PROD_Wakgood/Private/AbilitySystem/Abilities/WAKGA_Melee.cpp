// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\AbilitySystem\Abilities\WAKGA_Melee.h"

UWAKGA_Melee::UWAKGA_Melee()
{
	
	AbilityTags.AddTag(FWAKGameplayTags::Get().Character_Form_Melee);
	ActivationBlockedTags.AddTag(FWAKGameplayTags::Get().Character_Form_Normal);
	ActivationBlockedTags.AddTag(FWAKGameplayTags::Get().Character_Form_LongRange);
	ActivationBlockedTags.AddTag(FWAKGameplayTags::Get().Character_Form_Range);
}

void UWAKGA_Melee::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	ActivateAbilityAndChangeWeapon();
}
