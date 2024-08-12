// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakAmoeba.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAmoeba : public AMonster_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = List)
	TMap<int32, TSubclassOf<AMonster_Base>> MonsterList;

	// set true when detecting player
	bool bCanTransformation;
	
public:
	AWakAmoeba();

	FORCEINLINE void SetCanTransformation(bool bCan) { bCanTransformation = bCan; }
	FORCEINLINE bool CanTransformation() const { return bCanTransformation; }

	void CheckTransformation();
	void Transformation();
};
