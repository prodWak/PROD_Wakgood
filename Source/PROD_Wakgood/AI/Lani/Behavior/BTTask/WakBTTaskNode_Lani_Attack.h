// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WakBTTaskNode_Lani_Attack.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakBTTaskNode_Lani_Attack : public UBTTaskNode
{
	GENERATED_BODY()

	bool IsAttacking;

public:
	UWakBTTaskNode_Lani_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	// virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
