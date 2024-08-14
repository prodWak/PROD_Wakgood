// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_Dulgi.generated.h"

class AWakDulgi;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_Dulgi : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_Dulgi;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_Dulgi;

	TObjectPtr<AWakDulgi> OwningPawn;

	const FName Dulgi_TargetKey;

public:
	AWakAIC_Dulgi();

	virtual void Tick(float DeltaSeconds) override;

	const FName GetTargetKey() const { return Dulgi_TargetKey; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
