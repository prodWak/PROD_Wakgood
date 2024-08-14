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

public:
	AWakAIC_Ifari();

	static const FName Ifari_HomePosKey;
	static const FName Ifari_PatrolPosKey;
	static const FName Ifari_TargetKey;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
