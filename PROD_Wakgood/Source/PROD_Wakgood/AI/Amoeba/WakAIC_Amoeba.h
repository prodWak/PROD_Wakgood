// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_Amoeba.generated.h"

class AWakAmoeba;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_Amoeba : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_Amoeba;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_Amoeba;

	TObjectPtr<AWakAmoeba> OwningPawn;

	const FName Amoeba_HomePosKey;
	const FName Amoeba_PatrolPosKey;
	const FName Amoeba_CanTransformKey;

public:
	AWakAIC_Amoeba();

	const FName GetHomePosKey() const { return Amoeba_HomePosKey; }
	const FName GetPatrolPosKey() const { return Amoeba_PatrolPosKey; }
	const FName GetCanTransformKey() const { return Amoeba_CanTransformKey; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
