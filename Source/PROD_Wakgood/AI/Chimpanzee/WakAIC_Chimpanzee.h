// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_Chimpanzee.generated.h"

class AWakChimpanzee;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_Chimpanzee : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_Chimpanzee;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_Chimpanzee;

	UPROPERTY()
	TObjectPtr<AWakChimpanzee> OwningPawn;

public:
	AWakAIC_Chimpanzee();

	static const FName Chimpanzee_HomePosKey;
	static const FName Chimpanzee_PatrolPosKey;
	static const FName Chimpanzee_TargetKey;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
