// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_Chimpanzee_FindPatrolPos.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "PROD_Wakgood/AI/Chimpanzee/WakAIC_Chimpanzee.h"

UWakBTTask_Chimpanzee_FindPatrolPos::UWakBTTask_Chimpanzee_FindPatrolPos()
{
	NodeName = TEXT("Chimpanzee_FindPatrolPos");
	Radius = 500.0f;
}

EBTNodeResult::Type UWakBTTask_Chimpanzee_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_Chimpanzee* AIController = Cast<AWakAIC_Chimpanzee>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
		if (NavSys != nullptr)
		{
			FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AIController->GetHomePosKey());
			FNavLocation NextPatrol;

			if (NavSys->GetRandomPointInNavigableRadius(Origin, Radius, NextPatrol))
			{
				NextPatrol.Location.Y = 0;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AIController->GetPatrolPosKey(), NextPatrol.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
