// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTaskNode_Dakdulgi_FindPatrolPos.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "PROD_Wakgood/AI/Dakdulgi/WakAIC_Dakdulgi.h"

UWakBTTaskNode_Dakdulgi_FindPatrolPos::UWakBTTaskNode_Dakdulgi_FindPatrolPos()
{
	NodeName = TEXT("Dakdulgi_FindPatrolPos");
}

EBTNodeResult::Type UWakBTTaskNode_Dakdulgi_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (ControllingPawn != nullptr)
	{
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());

		if (NavSys != nullptr)
		{
			FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AWakAIC_Dakdulgi::Dakdulgi_HomePosKey);
			FNavLocation NextPatrol;

			if (NavSys->GetRandomPointInNavigableRadius(Origin, 500.0f, NextPatrol))
			{
				// Fixed Y-axis
				NextPatrol.Location.Y = 0;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AWakAIC_Dakdulgi::Dakdulgi_PatrolPosKey, NextPatrol.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}