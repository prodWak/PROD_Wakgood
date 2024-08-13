// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_Lani.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_Lani : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_Lani;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_Lani;

	const FName Lani_HomePosKey;
	const FName Lani_PatrolPosKey;
	const FName Lani_TargetKey;
	const FName Lani_IsDamagedKey;

public:
	AWakAIC_Lani();

	const FName GetHomePosKey() const { return Lani_HomePosKey; }
	const FName GetPatrolPosKey() const { return Lani_PatrolPosKey; }
	const FName GetTargetKey() const { return Lani_TargetKey; }
	const FName GetIsDamagedKey() const { return Lani_IsDamagedKey; }

protected:
	virtual void OnPossess(APawn* InPawn) override;

};
