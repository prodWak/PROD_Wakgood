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

	const FName Chimpanzee_HomePosKey;
	const FName Chimpanzee_PatrolPosKey;
	const FName Chimpanzee_TargetKey;

public:
	AWakAIC_Chimpanzee();

	const FName GetHomePosKey() const { return Chimpanzee_HomePosKey; }
	const FName GetPatrolPosKey() const { return Chimpanzee_PatrolPosKey; }
	const FName GetTargetKey() const { return Chimpanzee_TargetKey; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
