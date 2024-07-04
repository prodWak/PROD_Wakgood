// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "WAKInputConfig.h"
#include "WAKInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWAKInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass, typename PressedFuncType> //UserClass형 변수 
	void BindAbilityActions(const UWAKInputConfig* InputConfig, UserClass Object, PressedFuncType PressFunc)
	{
		check(InputConfig);
		for(FWAKInputAction Action : InputConfig->AbilityInputAction)
		{
			if(Action.InputAction && Action.InputTag.IsValid()) //태그 
			{
				BindAction(Action.InputAction, ETriggerEvent::Started,Object,PressFunc,Action.InputTag); //UInputAction, 트리거 타입, 캐릭터 객체, 사용할 함수, 함수에 넘길 파라미터  
			}
		}
	}
};
