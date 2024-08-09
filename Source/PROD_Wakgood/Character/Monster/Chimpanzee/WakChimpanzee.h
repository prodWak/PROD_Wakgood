// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakChimpanzee.generated.h"

UENUM()
enum class EChimpanzeeMode : uint8
{
	Normal UMETA(DisplayName = "NormalMode"),
	Angry UMETA(DisplayName = "AngryMode")
};

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

	UPROPERTY()
	float AngryGaugeAmount;

	FTimerHandle IncreaseAngryGaugeHandle;
	FTimerHandle DecreaseAngryGaugeHandle;

	EChimpanzeeMode Mode;

public:
	AWakChimpanzee();

	void StartIncreaseAngryGaugeTimer();
	void StartDecreaseAngryGaugeTImer();

	void IncreaseAngryGauge_Recursive();	
	void DecreaseAngryGauge_Recursive();	

	void SetMode(EChimpanzeeMode Type);
};
