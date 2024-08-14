// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_Chimpanzee_FindPatrolPos.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "PROD_Wakgood/AI/Chimpanzee/WakAIC_Chimpanzee.h"

UWakBTTask_Chimpanzee_FindPatrolPos::UWakBTTask_Chimpanzee_FindPatrolPos()
{
	NodeName = TEXT("Chimpanzee_FindPatrolPos");
}

EBTNodeResult::Type UWakBTTask_Chimpanzee_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
		if (NavSys != nullptr)
		{
			FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AWakAIC_Chimpanzee::Chimpanzee_HomePosKey);
			FNavLocation NextPatrol;

			if (NavSys->GetRandomPointInNavigableRadius(Origin, 500.0f, NextPatrol))
			{
				NextPatrol.Location.Y = 0;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AWakAIC_Chimpanzee::Chimpanzee_PatrolPosKey, NextPatrol.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
