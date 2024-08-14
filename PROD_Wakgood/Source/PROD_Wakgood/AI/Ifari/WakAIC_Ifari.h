// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_Ifari.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_Ifari : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_Ifari;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_Ifari;

	const FName Ifari_HomePosKey;
	const FName Ifari_PatrolPosKey;
	const FName Ifari_TargetKey;

public:
	AWakAIC_Ifari();

	const FName GetHomePosKey() const { return Ifari_HomePosKey; }
	const FName GetPatrolPosKey() const { return Ifari_PatrolPosKey; }
	const FName GetTargetKey() const { return Ifari_TargetKey; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
