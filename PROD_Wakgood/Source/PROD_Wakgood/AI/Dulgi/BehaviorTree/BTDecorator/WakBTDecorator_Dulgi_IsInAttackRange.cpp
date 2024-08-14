// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTDecorator_Dulgi_IsInAttackRange.h"

#include "PROD_Wakgood/AI/Dulgi/WakAIC_Dulgi.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"

UWakBTDecorator_Dulgi_IsInAttackRange::UWakBTDecorator_Dulgi_IsInAttackRange()
{
    NodeName = TEXT("Dulgi_CanAttack");

    AttackRadius = 600.0f;
}

bool UWakBTDecorator_Dulgi_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (ControllingPawn != nullptr)
    {
        AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AWakAIC_Dulgi::Dulgi_TargetKey));
        if (Target != nullptr)
        {
            bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRadius);
            return bResult;
        }
    }

    return false;
}
