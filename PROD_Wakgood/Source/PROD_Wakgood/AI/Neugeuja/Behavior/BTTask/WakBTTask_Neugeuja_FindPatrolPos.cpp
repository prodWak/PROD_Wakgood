// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_Neugeuja_FindPatrolPos.h"

#include "PROD_Wakgood/AI/Neugeuja/WakAIC_Neugeuja.h"
#include "PROD_Wakgood/Character/Monster/Neugeuja/WakNeugeuja.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "NavigationSystem.h"

UWakBTTask_Neugeuja_FindPatrolPos::UWakBTTask_Neugeuja_FindPatrolPos()
{
	NodeName = TEXT("Neugeuja_FindPatrolPos");
	Radius = 500.0f;
}

EBTNodeResult::Type UWakBTTask_Neugeuja_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AWakAIC_Neugeuja* AIController = Cast< AWakAIC_Neugeuja>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));
	if (ControllingPawn != nullptr && AIController != nullptr)
	{
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
		AWakNeugeuja* AIOwner = Cast<AWakNeugeuja>(ControllingPawn);

		if (NavSys != nullptr && !AIOwner->IsTeleporting())
		{
			FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AIController->GetHomePoskey());
			FNavLocation NextPatrol;

			/*if (AIOwner->IsTeleporting())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AIController->GetPatrolPosKey(), ControllingPawn->GetActorLocation());
				return EBTNodeResult::Succeeded;
			}*/

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
