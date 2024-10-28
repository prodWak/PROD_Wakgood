// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Normal/WAKGA_FormChangeNormal.h"
#include "AbilitySystemComponent.h"
#include "WAKTag.h"
#include "Player/WakPlayerState.h"

UWAKGA_FormChangeNormal::UWAKGA_FormChangeNormal()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(FWAKGameplayTags::Get().Ability_FormChange_Normal);
	
	ActivationOwnedTags.AddTag(FWAKGameplayTags::Get().Character_Form_Normal);
	ActivationBlockedTags.AddTag(FWAKGameplayTags::Get().Character_Form_Normal);
}

void UWAKGA_FormChangeNormal::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	TestPlayerState =  Cast<AWakPlayerState>(CurrentActorInfo->OwnerActor.Get());
	SettingFormChange(FString("Normal"));
}

void UWAKGA_FormChangeNormal::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

