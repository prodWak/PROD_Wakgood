// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WakGameplayAbility.h"

#include "AbilitySystem/WakAbilitySystemComponent.h"
#include "Components/Combat/WakPawnCombatComponent.h"

void UWakGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EWakAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UWakGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EWakAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UWakPawnCombatComponent* UWakGameplayAbility::GetWakPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UWakPawnCombatComponent>();
}

UWakAbilitySystemComponent* UWakGameplayAbility::GetWakAbilitySystemComponentFromActorInfo() const
{
	return Cast<UWakAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
