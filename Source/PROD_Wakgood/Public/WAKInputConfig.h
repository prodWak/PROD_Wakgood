// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WAKInputConfig.generated.h"

class UInputAction;
/**
 * 
 */
USTRUCT()
struct FWAKInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	const class UInputAction* InputAction = nullptr;
	UPROPERTY(EditAnywhere)
	FGameplayTag InputTag = FGameplayTag();
	
	
};


UCLASS()
class PROD_WAKGOOD_API UWAKInputConfig : public UDataAsset
{
	GENERATED_BODY()

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag InputTag, bool bLogNotFouund = false) const;
public:
	UPROPERTY(EditAnywhere)
	TArray<FWAKInputAction> AbilityInputAction;
};
