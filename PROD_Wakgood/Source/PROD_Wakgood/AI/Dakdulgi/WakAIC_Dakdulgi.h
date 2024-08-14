// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_Dakdulgi.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_Dakdulgi : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_Dakdulgi;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_Dakdulgi;

	const FName Dakdulgi_HomePosKey;
	const FName Dakdulgi_PatrolPosKey;
	const FName Dakdulgi_TargetKey;

public:
	AWakAIC_Dakdulgi();

	const FName GetHomePosKey() const { return Dakdulgi_HomePosKey; }
	const FName GetPatrolPosKey() const { return Dakdulgi_PatrolPosKey; }
	const FName GetTargetKey() const { return Dakdulgi_TargetKey; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
