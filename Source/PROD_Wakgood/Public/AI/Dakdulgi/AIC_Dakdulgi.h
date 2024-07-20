// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AIC_Base.h"
#include "AIC_Dakdulgi.generated.h"

class AWakgood_Dakdulgi;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AAIC_Dakdulgi : public AAIC_Base
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<APawn> TargetPawn;

	UPROPERTY()
	TObjectPtr<AWakgood_Dakdulgi> OwningDulgi;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_Dakdulgi;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_Dakdulgi;

	// Timer
	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;

	void OnRepeatTimer();

public:
	AAIC_Dakdulgi();

	static const FName HomePosKey;
	static const FName PatrolPosKey;

	// Target Setting
	void SetTargetPawn(APawn* Target);
	void InitTargetPawn();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	void Chase();
};
