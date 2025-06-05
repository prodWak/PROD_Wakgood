// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartUpData/WakStartUpDataAssetBase.h"
#include "WakStartUpEnemyDataAsset.generated.h"

class UWakGameplayAbilityEnemy;
class UWakAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakStartUpEnemyDataAsset : public UWakStartUpDataAssetBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWakAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Wak|StartUpData")
	TArray<TSubclassOf<UWakGameplayAbilityEnemy>> EnemyCombatAbilities;
};
