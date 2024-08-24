// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_PoopDog_FindPatrolPos.h"

#include "PROD_Wakgood/AI/PoopDog/WakAIC_PoopDog.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UWakBTTask_PoopDog_FindPatrolPos::UWakBTTask_PoopDog_FindPatrolPos()
{
	NodeName = TEXT("PoopDog_FindPatrolPos");
	Radius = 600.0f;
}

EBTNodeResult::Type UWakBTTask_PoopDog_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_PoopDog* AIController = Cast<AWakAIC_PoopDog>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));
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
