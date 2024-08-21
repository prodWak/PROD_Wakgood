// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_Neugeuja.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_Neugeuja : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_Neugeuja;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_Neugeuja;

	const FName Neugeuja_HomePosKey;
	const FName Neugeuja_PatrolPosKey;
	const FName Neugeuja_TargetKey;

public:
	AWakAIC_Neugeuja();

	const FName GetHomePoskey() const { return Neugeuja_HomePosKey; }
	const FName GetPatrolPosKey() const { return Neugeuja_PatrolPosKey; }
	const FName GetTargetKey() const { return Neugeuja_TargetKey; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
