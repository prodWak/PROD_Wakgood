// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_JuMob_FindPatrolPos.h"

#include "PROD_Wakgood/AI/JuMob/WakAIC_JuMob.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UWakBTTask_JuMob_FindPatrolPos::UWakBTTask_JuMob_FindPatrolPos()
{
	NodeName = TEXT("JuMob_FindPatrolPos");
	Radius = 600.0f;
}

EBTNodeResult::Type UWakBTTask_JuMob_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_JuMob* AIController = Cast<AWakAIC_JuMob>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
		if (AIController != nullptr && NavSys != nullptr)
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
