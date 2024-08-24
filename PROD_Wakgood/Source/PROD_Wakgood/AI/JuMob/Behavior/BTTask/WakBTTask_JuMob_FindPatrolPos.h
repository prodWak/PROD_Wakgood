// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WakBTTask_JuMob_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakBTTask_JuMob_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

	float Radius;

public:
	UWakBTTask_JuMob_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
