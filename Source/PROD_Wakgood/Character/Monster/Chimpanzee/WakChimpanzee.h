// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakChimpanzee.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackDelegate);

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

	UPROPERTY()
	bool bCanAttack;

	FTimerHandle IncreaseAngryGaugeHandle;
	FTimerHandle DecreaseAngryGaugeHandle;

	EChimpanzeeMode Mode;

	void StartDecreaseAngryGaugeTImer();

	void IncreaseAngryGauge_Recursive();
	void DecreaseAngryGauge_Recursive();

public:
	AWakChimpanzee();

	FORCEINLINE bool GetCanAttack() const { return bCanAttack; }

	void StartIncreaseAngryGaugeTimer();
	void SetMode(EChimpanzeeMode Type);

	void Attack();
	FOnAttackDelegate OnAttackDelegate;
};
