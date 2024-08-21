// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_Lani_FindPatrolPos.h"

#include "PROD_Wakgood/AI/Lani/WakAIC_Lani.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UWakBTTask_Lani_FindPatrolPos::UWakBTTask_Lani_FindPatrolPos()
{
	NodeName = TEXT("Lani_FindPatrolPos");
	Radius = 500.0f;
}

EBTNodeResult::Type UWakBTTask_Lani_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_Lani* AIController = Cast<AWakAIC_Lani>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));

		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
		if (NavSys != nullptr)
		{
			FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AIController->GetHomePosKey());
			FNavLocation NextPatrol;

			if (NavSys->GetRandomPointInNavigableRadius(Origin, Radius, NextPatrol))
			{
				NextPatrol.Location.Y = 0;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AIController->GetPatrolPosKey(), NextPatrol);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
