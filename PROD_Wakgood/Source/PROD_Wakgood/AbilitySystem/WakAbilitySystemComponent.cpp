// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WakAbilitySystemComponent.h"
#include "WakGameplayTags.h"

void UWakAbilitySystemComponent::OnAbilityInputPressed(FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))
		{
			continue;
		}

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UWakAbilitySystemComponent::OnAbilityInputReleased(FGameplayTag& InInputTag)
{
	unimplemented();
}
