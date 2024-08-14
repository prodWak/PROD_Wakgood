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

public:
	AWakAIC_Dakdulgi();

	static const FName Dakdulgi_HomePosKey;
	static const FName Dakdulgi_PatrolPosKey;
	static const FName Dakdulgi_TargetKey;

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
