// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WakBTTask_Neugeuja_SpawnMonster.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakBTTask_Neugeuja_SpawnMonster : public UBTTaskNode
{
	GENERATED_BODY()

	bool IsSpawned;

public:
	UWakBTTask_Neugeuja_SpawnMonster();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
