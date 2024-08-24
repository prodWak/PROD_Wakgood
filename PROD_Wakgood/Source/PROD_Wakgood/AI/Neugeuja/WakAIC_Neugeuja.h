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

public:
	AWakAIC_Neugeuja();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
