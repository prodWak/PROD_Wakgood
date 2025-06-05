// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WakPawnCombatComponent.h"
#include "WakPlayerCombatComponent.generated.h"

class AWakPlayerWeapon;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakPlayerCombatComponent : public UWakPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Wak|Player")
	AWakPlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Wak|Player")
	AWakPlayerWeapon* GetPlayerCurrentEquippedWeapon() const;
	
	UFUNCTION(BlueprintCallable, Category = "Wak|Player")
	float GetPlayerCurrentEquippedWeaponDamageAtLevel(float InLevel) const;
	
	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
