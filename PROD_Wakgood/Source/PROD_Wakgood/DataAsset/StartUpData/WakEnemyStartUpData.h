// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartUpData/WakStartUpDataBase.h"
#include "WakEnemyStartUpData.generated.h"

class UWakEnemyGameplayAbility;
class UWakAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakEnemyStartUpData : public UWakStartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWakAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Wak|StartUpData")
	TArray<TSubclassOf<UWakEnemyGameplayAbility>> EnemyCombatAbilities;
};
