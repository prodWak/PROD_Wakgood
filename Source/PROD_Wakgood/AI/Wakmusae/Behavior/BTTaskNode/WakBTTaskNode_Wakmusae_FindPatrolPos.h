// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WakBTTaskNode_Wakmusae_FindPatrolPos.generated.h"

// header error

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakBTTaskNode_Wakmusae_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UWakBTTaskNode_Wakmusae_FindPatrolPos();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
