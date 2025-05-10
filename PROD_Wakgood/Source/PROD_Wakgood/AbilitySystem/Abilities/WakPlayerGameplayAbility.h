// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WakGameplayAbility.h"
#include "WakPlayerGameplayAbility.generated.h"

class UWakPlayerCombatComponent;
class AWakPlayerController;
class AWakWakGoodCharacter;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakPlayerGameplayAbility : public UWakGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Wak|Ability")
	AWakWakGoodCharacter* GetWakPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Wak|Ability")
	AWakPlayerController* GetWakPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Wak|Ability")
	UWakPlayerCombatComponent* GetWakPlayerCombatComponentFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Wak|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage);
	
private:
	TWeakObjectPtr<AWakWakGoodCharacter> CachedWakPlayerCharacter;
	TWeakObjectPtr<AWakPlayerController> CachedWakPlayerController;
};
