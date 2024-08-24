// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_BacteriaDan.generated.h"


/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_BacteriaDan : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_BacteriaDan;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_BacteriaDan;

public:
	AWakAIC_BacteriaDan();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
