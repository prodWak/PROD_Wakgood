// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WakBTTask_PoopDog_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakBTTask_PoopDog_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY()
	float Radius;

public:
	UWakBTTask_PoopDog_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
