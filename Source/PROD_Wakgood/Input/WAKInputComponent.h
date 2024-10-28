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
	UWAKInputComponent();
	template<class UserClass, typename PressedFuncType, typename ReleaseFuncType> //UserClass형 변수 
	void BindAbilityActions(const UWAKInputConfig* InputConfig, UserClass Object, PressedFuncType PressFunc,ReleaseFuncType ReleaseFunc);
	
};

template<class UserClass, typename PressedFuncType, typename ReleaseFuncType> //UserClass형 변수 
	void UWAKInputComponent::BindAbilityActions(const UWAKInputConfig* InputConfig, UserClass Object, PressedFuncType PressFunc, ReleaseFuncType ReleaseFunc)
{
	check(InputConfig);
	for(FWAKInputAction Action : InputConfig->AbilityInputAction) //InputConfig(InputAction - Tag가 담겨있음)
	{
		if(Action.InputAction && Action.InputTag.IsValid()) //태그 
		{
			if(PressFunc)
				BindAction(Action.InputAction, ETriggerEvent::Started,Object,PressFunc,Action.InputTag); //UInputAction, 트리거 타입, 캐릭터 객체, 사용할 함수, 함수에 넘길 파라미터,BindAction에 필수 파라미터 이상으로 집어넣는 파라미터는 인자로 넘어간다.  
			//InputConfig에 들어있는 InputAction - Tag를 이용해서 바인딩하기.
			if(ReleaseFunc)
				BindAction(Action.InputAction, ETriggerEvent::Completed,Object,ReleaseFunc,Action.InputTag);
		}
	}
}
