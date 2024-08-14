// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTaskNode_Ifari_FindPatrolPos.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "PROD_Wakgood/AI/Ifari/WakAIC_Ifari.h"

UWakBTTaskNode_Ifari_FindPatrolPos::UWakBTTaskNode_Ifari_FindPatrolPos()
{
    NodeName = TEXT("Ifari_FindPatrolPos");
}

EBTNodeResult::Type UWakBTTaskNode_Ifari_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

    if (ControllingPawn != nullptr)
    {
        AWakAIC_Ifari* AIController = Cast<AWakAIC_Ifari>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));

        UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());

        if (NavSys != nullptr)
        {
            FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AIController->GetHomePosKey());
            FNavLocation NextPatrol;

            if (NavSys->GetRandomPointInNavigableRadius(Origin, 500.0f, NextPatrol))
            {
                // Fixed Y axis
                NextPatrol.Location.Y = 0;
                OwnerComp.GetBlackboardComponent()->SetValueAsVector(AIController->GetPatrolPosKey(), NextPatrol);
                return EBTNodeResult::Succeeded;
            }
        }
    }

    return EBTNodeResult::Failed;
}
