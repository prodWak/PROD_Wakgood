// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindPatrolPos.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "PROD_Wakgood/AI/Dakdulgi/AIC_Dakdulgi.h"

UBTTaskNode_FindPatrolPos::UBTTaskNode_FindPatrolPos()
{
	NodeName = TEXT("Dakdulgi_FindPatrolPos");
}

EBTNodeResult::Type UBTTaskNode_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (ControllingPawn != nullptr)
	{
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());

		if (NavSys != nullptr)
		{
			FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AAIC_Dakdulgi::Dakdulgi_HomePosKey);
			FNavLocation NextPatrol;

			if (NavSys->GetRandomPointInNavigableRadius(Origin, 500.0f, NextPatrol))
			{
				// ��� �̵�
				NextPatrol.Location.Y = 0;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AAIC_Dakdulgi::Dakdulgi_PatrolPosKey, NextPatrol.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}