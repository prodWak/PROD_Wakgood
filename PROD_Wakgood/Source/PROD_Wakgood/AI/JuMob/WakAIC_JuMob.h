// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_JuMob.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_JuMob : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EdiTDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_JuMob;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_JuMob;

	const FName IsDetectTargetKey;

public:
	AWakAIC_JuMob();

	const FName GetIsDetectTarget() const { return IsDetectTargetKey; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
