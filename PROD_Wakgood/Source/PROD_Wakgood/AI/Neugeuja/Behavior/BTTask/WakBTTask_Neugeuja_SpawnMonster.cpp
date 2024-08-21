// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_Neugeuja_SpawnMonster.h"

#include "PROD_Wakgood/AI/Neugeuja/WakAIC_Neugeuja.h"
#include "PROD_Wakgood/Character/Monster/Neugeuja/WakNeugeuja.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTTask_Neugeuja_SpawnMonster::UWakBTTask_Neugeuja_SpawnMonster()
{
	NodeName = TEXT("Neugeuja_SpawnMonster");
	IsSpawned = false;
}

EBTNodeResult::Type UWakBTTask_Neugeuja_SpawnMonster::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakNeugeuja* AIOwner = Cast<AWakNeugeuja>(ControllingPawn);
		if (AIOwner != nullptr && !AIOwner->IsSpawnCompleted())
		{
			AIOwner->SpawnRandomMonster();
			AIOwner->SetIsSpawnCompleted(true);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
