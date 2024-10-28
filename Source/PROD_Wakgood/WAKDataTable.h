// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "WAKDataTable.generated.h"

USTRUCT()
struct FCharacterStatus : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="Primary Category")
	float Health;
	
	UPROPERTY(EditAnywhere, Category="Primary Category")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category="Primary Category")
	float Damage;
	
	UPROPERTY(EditAnywhere, Category="Primary Category")
	float Resist;

	UPROPERTY(EditAnywhere, Category="Primary Category")
	FGameplayTag FormTag;

	UPROPERTY(EditAnywhere)
	FGameplayTag TypeTag;
	
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<UGameplayAbility>,FGameplayTag> MoveSet;

	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;
};

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
struct FSkillInfo : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName SkillName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ManaCost;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CastTime;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGameplayTag CCDuration;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGameplayTag DebuffTag;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGameplayTag BuffTag;
};

/*USTRUCT()
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
	
};*/