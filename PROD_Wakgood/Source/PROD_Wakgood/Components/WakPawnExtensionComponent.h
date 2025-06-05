// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WakPawnExtensionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROD_WAKGOOD_API UWakPawnExtensionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	template<class T>
	T* GetOwningPawn() const
	{
		// T가 APawn으로 변환 가능한지
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, TEXT("'T' Template Parameter GetPawn must be derived from APawn."));
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template<class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, TEXT("'T' Template Parameter to GetController must be derived from AController."));
		return GetOwningPawn<APawn>()->GetController<T>();
	}
};
