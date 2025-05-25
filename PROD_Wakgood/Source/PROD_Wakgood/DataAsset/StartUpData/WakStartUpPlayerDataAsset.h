// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartUpData/WakStartUpDataAssetBase.h"
#include "WakGameplayTags.h"
#include "WakStartUpPlayerDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FWakPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UWakGameplayAbilityBase> AbilityToGrant;

	bool IsValid() const;
};

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakStartUpPlayerDataAsset : public UWakStartUpDataAssetBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWakAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Wak|StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FWakPlayerAbilitySet> WakPlayerStartUpAbilitySets;
	
};
