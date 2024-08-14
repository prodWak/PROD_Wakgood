// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_BacteriaDan_FindPatrolPos.h"

#include "PROD_Wakgood/AI/BacteriaDan/WakAIC_BacteriaDan.h"
#include "PROD_Wakgood/Character/Monster/BacteriaDan/WakBacteriaDan.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTTask_BacteriaDan_FindPatrolPos::UWakBTTask_BacteriaDan_FindPatrolPos()
{
	NodeName = TEXT("BacteriaDan_FindPatrolPos");
}

EBTNodeResult::Type UWakBTTask_BacteriaDan_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AWakBacteriaDan* OwnerPawn = Cast<AWakBacteriaDan>(ControllingPawn);

	// Get OwnerPawn
	if (OwnerPawn != nullptr)
	{
		AWakAIC_BacteriaDan* AIController = Cast<AWakAIC_BacteriaDan>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));

		// Get NavSys
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
		if (NavSys != nullptr)
		{
			FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AIController->GetHomePosKey());
			FNavLocation NextPatrol;

			// Set RandomPoint
			if (NavSys->GetRandomPointInNavigableRadius(Origin, 500.0f, NextPatrol))
			{
				if (NextPatrol.Location.X < Origin.X)
				{
					OwnerPawn->SetLaunchDirection(-1);
				}
				else if (NextPatrol.Location.X > Origin.X)
				{
					OwnerPawn->SetLaunchDirection(1);
				}
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
