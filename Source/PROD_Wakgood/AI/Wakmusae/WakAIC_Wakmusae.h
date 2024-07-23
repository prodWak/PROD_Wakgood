// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/AIC_Base.h"
#include "WakAIC_Wakmusae.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_Wakmusae : public AAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_Wakmusae;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_Wakmusae;

public:
	AWakAIC_Wakmusae();

	static const FName Wakmusae_HomePosKey;
	static const FName Wakmusae_PatrolPosKey;
	static const FName Wakmusae_TargetKey;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
