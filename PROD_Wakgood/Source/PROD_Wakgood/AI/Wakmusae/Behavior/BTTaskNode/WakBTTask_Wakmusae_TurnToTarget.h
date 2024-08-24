// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WakBTTask_Wakmusae_TurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakBTTask_Wakmusae_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()

	FRotator TargetRot;
	FRotator ControllingPawnRot;

public:
	UWakBTTask_Wakmusae_TurnToTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
