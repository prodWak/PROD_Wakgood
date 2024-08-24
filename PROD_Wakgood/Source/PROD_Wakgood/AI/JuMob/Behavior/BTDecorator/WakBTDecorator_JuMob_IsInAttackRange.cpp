// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTDecorator_JuMob_IsInAttackRange.h"

#include "PROD_Wakgood/AI/JuMob/WakAIC_JuMob.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTDecorator_JuMob_IsInAttackRange::UWakBTDecorator_JuMob_IsInAttackRange()
{
    NodeName = TEXT("JuMob_IsInAttackRange");

    AttackRadius = 200.0f;
}

bool UWakBTDecorator_JuMob_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (ControllingPawn != nullptr)
    {
        AWakAIC_JuMob* AIController = Cast<AWakAIC_JuMob>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));
        AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AIController->GetTargetKey()));

        if (Target != nullptr)
        {
            bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRadius);
            return bResult;
        }
    }

    return false;
}
