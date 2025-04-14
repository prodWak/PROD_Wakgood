// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/Input/WakInputConfig.h"

UInputAction* UWakInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag)
{
	for (const FWakInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}
