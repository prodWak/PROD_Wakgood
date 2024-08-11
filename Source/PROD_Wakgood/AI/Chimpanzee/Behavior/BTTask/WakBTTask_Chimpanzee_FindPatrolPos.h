// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WakBTTask_Chimpanzee_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakBTTask_Chimpanzee_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UWakBTTask_Chimpanzee_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
