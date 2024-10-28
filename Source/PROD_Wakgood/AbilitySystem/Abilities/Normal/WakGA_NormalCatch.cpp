// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Normal/WakGA_NormalCatch.h"

UWakGA_NormalCatch::UWakGA_NormalCatch()
{
	StartUpTag = FWAKGameplayTags::Get().InputTag_W;
	AbilityTags.AddTag(FWAKGameplayTags::Get().InputTag_W);
}

void UWakGA_NormalCatch::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp,Warning,TEXT("Activate Normal Catch"));
}
