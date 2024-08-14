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

public:
	AWakAIC_Amoeba();

	static const FName Amoeba_HomePosKey;
	static const FName Amoeba_PatrolPosKey;
	static const FName Amoeba_CanTransformKey;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
