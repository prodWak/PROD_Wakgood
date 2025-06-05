// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScalableFloat.h"
#include "Items/Weapons/WakWeaponBase.h"
#include "WakPlayerWeapon.generated.h"

struct FWakPlayerAbilitySet;
class UInputMappingContext;
class UWakLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FWakPlayerWeaponData
{
	GENERATED_BODY()

	// 무기 별 사용 가능한 능력
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wak|InputTag")
	// TArray<FWakPlayerAbilitySet> DefaultWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;
};

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakPlayerWeapon : public AWakWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wak|WeaponData")
	FWakPlayerWeaponData PlayerWeaponData;
	
};
