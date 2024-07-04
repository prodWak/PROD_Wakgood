// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\AbilitySystem\Abilities\WAKGA_Range.h"

UWAKGA_Range::UWAKGA_Range()
{
	AbilityTags.AddTag(FWAKGameplayTags::Get().Character_Form_Range);
	ActivationBlockedTags.AddTag(FWAKGameplayTags::Get().Character_Form_Normal);
	ActivationBlockedTags.AddTag(FWAKGameplayTags::Get().Character_Form_Melee);
	ActivationBlockedTags.AddTag(FWAKGameplayTags::Get().Character_Form_LongRange);
}

void UWAKGA_Range::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	ActivateAbilityAndChangeWeapon();
}
