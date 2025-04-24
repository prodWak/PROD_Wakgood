// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WakGameplayTags.h"
#include "InputTriggers.h"
#include "WakInputConfig.generated.h"

class UInputMappingContext;
class UInputAction;

USTRUCT(BlueprintType)
struct FWakInputActionConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETriggerEvent PressedTriggerEvent = ETriggerEvent::Started;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETriggerEvent ReleasedTriggerEvent = ETriggerEvent::Completed;

	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}
};

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FWakInputActionConfig> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FWakInputActionConfig> AbilityInputActions;

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag);
};
