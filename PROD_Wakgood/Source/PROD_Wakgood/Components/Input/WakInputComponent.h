// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/Input/WakInputConfig.h"
#include "WakInputComponent.generated.h"

class UWakInputConfig;
class UInputAction;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(UWakInputConfig* InInputConfig, const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
	
	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(UWakInputConfig* InInputConfig, UserObject* ContextObject,
		CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

template <class UserObject, typename CallbackFunc>
void UWakInputComponent::BindNativeInputAction(UWakInputConfig* InInputConfig, const FGameplayTag& InInputTag,
	ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data asset is null. can not proceed with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template <class UserObject, typename CallbackFunc>
void UWakInputComponent::BindAbilityInputAction(UWakInputConfig* InInputConfig, UserObject* ContextObject,
	CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null. can not proceed with binding"));

	for (const FWakInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid())
		{
			continue;
		}

		BindAction(AbilityInputActionConfig.InputAction, AbilityInputActionConfig.PressedTriggerEvent, ContextObject,
			InputPressedFunc, AbilityInputActionConfig.InputTag);
		
		BindAction(AbilityInputActionConfig.InputAction, AbilityInputActionConfig.ReleasedTriggerEvent, ContextObject,
			InputReleasedFunc, AbilityInputActionConfig.InputTag);
	}
}
