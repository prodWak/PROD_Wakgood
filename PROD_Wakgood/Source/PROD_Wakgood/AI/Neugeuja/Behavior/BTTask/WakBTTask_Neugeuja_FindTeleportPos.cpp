// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_Neugeuja_FindTeleportPos.h"

#include "PROD_Wakgood/AI/Neugeuja/WakAIC_Neugeuja.h"
#include "PROD_Wakgood/Character/Monster/Neugeuja/WakNeugeuja.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTTask_Neugeuja_FindTeleportPos::UWakBTTask_Neugeuja_FindTeleportPos()
{
	NodeName = TEXT("Neugeuja_FindTeleportPos");
}

EBTNodeResult::Type UWakBTTask_Neugeuja_FindTeleportPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakNeugeuja* AIOwner = Cast<AWakNeugeuja>(ControllingPawn);
		AWakAIC_Neugeuja* AIController = Cast<AWakAIC_Neugeuja>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));

		if (AIOwner != nullptr && !AIOwner->IsTeleporting())
		{
			UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
			
			if (NavSys != nullptr)
			{
				FVector Origin = ControllingPawn->GetActorLocation();
				FNavLocation TeleportingLocation;

				if (NavSys->GetRandomPointInNavigableRadius(Origin, 2000.0f, TeleportingLocation))
				{
					TeleportingLocation.Location.Y = 0;

					if (AIOwner->TeleportTo(TeleportingLocation.Location, AIOwner->GetActorRotation()))
					{
						AIOwner->SetIsTeleporting(true);
						OwnerComp.GetBlackboardComponent()->SetValueAsObject(AIController->GetTargetKey(), nullptr);
						return EBTNodeResult::Succeeded;
					}
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
