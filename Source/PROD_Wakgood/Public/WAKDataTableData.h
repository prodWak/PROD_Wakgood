// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "WAKDataTableData.generated.h"



USTRUCT()
struct FWeaponDT : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> WeaponMesh;
	
};

USTRUCT()
struct FCharacterStatus : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Health;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MinimumDamage = 0.1f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaximumDamage = 1.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float JumpPower;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BaseRes;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ChangeDuration = 180.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName TypeWeakness;
	
};