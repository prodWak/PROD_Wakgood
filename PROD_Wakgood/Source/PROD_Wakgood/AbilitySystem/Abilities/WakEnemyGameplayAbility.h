// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WakGameplayAbility.h"
#include "WakEnemyGameplayAbility.generated.h"

class AWakEnemyCharacter;
class UWakEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakEnemyGameplayAbility : public UWakGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Wak|Ability")
	AWakEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Wak|Ability")
	UWakEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	UPROPERTY()
	TWeakObjectPtr<AWakEnemyCharacter> CachedWakEnemyCharacter;
};
