// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakChimpanzee.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakChimpanzee : public AMonster_Base
{
	GENERATED_BODY()

	UPROPERTY()
	float MaxAngryGauge;

	UPROPERTY()
	float CurrentAngryGauge;

	FTimerHandle IncreaseAngryGaugeHandle;


public:
	AWakChimpanzee();

	void StartAngryGaugeTimer();
	void IncreaseAngryGauge_Recursive();	
};
