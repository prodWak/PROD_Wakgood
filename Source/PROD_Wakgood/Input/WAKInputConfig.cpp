// Fill out your copyright notice in the Description page of Project Settings.


#include "WAKInputConfig.h"

const UInputAction* UWAKInputConfig::FindAbilityInputActionForTag(const FGameplayTag InputTag, bool bLogNotFouund) const
{
	for(const FWAKInputAction Action : AbilityInputAction)
	{
		if(InputTag == Action.InputTag &&Action.InputAction)
		{
			return Action.InputAction;
		}
	}
	return nullptr;
}
