// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/Input/WakInputConfigDataAsset.h"

UInputAction* UWakInputConfigDataAsset::FindNativeInputActionByTag(const FGameplayTag& InInputTag)
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
