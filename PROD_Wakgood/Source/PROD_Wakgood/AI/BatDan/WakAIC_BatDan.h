// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_BatDan.generated.h"

class AWakBatDan;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_BatDan : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_BatDan;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_BatDan;

	TObjectPtr<AWakBatDan> OwningPawn;

	const FName BatDan_TargetKey;

public:
	AWakAIC_BatDan();

	const FName GetTargetKey() const { return BatDan_TargetKey; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
