// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WakGameplayAbilityBase.h"
#include "WakGameplayAbilityPlayer.generated.h"

class UWakPlayerCombatComponent;
class AWakPlayerController;
class AWakWakGoodCharacter;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakGameplayAbilityPlayer : public UWakGameplayAbilityBase
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
	UPROPERTY()
	TWeakObjectPtr<AWakWakGoodCharacter> CachedWakPlayerCharacter;

	UPROPERTY()
	TWeakObjectPtr<AWakPlayerController> CachedWakPlayerController;
};
