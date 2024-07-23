// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTaskNode_Wakmusae_FindPatrolPos.h"


#include "PROD_Wakgood/AI/Wakmusae/WakAIC_Wakmusae.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UWakBTTaskNode_Wakmusae_FindPatrolPos::UWakBTTaskNode_Wakmusae_FindPatrolPos()
{
	NodeName = TEXT("Wakmusae_FindPatrolPos");
}

EBTNodeResult::Type UWakBTTaskNode_Wakmusae_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (ControllingPawn != nullptr)
	{
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());

		if (NavSys != nullptr)
		{
			FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AWakAIC_Wakmusae::Wakmusae_HomePosKey);
			FNavLocation NextPatrol;

			if (NavSys->GetRandomPointInNavigableRadius(Origin, 500.0f, NextPatrol))
			{
				// ���� �ʿ�
				NextPatrol.Location.Y = 0;
				NextPatrol.Location.Z = 0;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AWakAIC_Wakmusae::Wakmusae_PatrolPosKey, NextPatrol.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
