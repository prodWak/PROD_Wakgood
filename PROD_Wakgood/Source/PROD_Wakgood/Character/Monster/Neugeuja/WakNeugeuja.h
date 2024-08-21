// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakNeugeuja.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakNeugeuja : public AMonster_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = List)
	TMap<int32, TSubclassOf<AMonster_Base>> MonsterList;

	int32 Key1, Key2, Interval;

	UPROPERTY(VisibleAnywhere)
	bool bIsSpawnCompleted;

	UPROPERTY(VisibleAnywhere)
	bool bIsTeleporting;

	void SetKey();
	void SetInterval();

	void SpawnRandomMonster_One();
	void SpawnRandomMonster_Two();

public:
	AWakNeugeuja();

	FORCEINLINE bool IsSpawnCompleted() const { return bIsSpawnCompleted; }
	FORCEINLINE void SetIsSpawnCompleted(bool IsSpawned) { bIsSpawnCompleted = IsSpawned; }

	FORCEINLINE bool IsTeleporting() const { return bIsTeleporting; }
	FORCEINLINE void SetIsTeleporting(bool IsTeleported) { bIsTeleporting = IsTeleported; }

	void SpawnRandomMonster();

};
