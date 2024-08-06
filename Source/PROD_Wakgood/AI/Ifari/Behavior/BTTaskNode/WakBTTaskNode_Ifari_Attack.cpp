// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTaskNode_Ifari_Attack.h"

#include "PROD_Wakgood/AI/Ifari/WakAIC_Ifari.h"
#include "PROD_Wakgood/Character/Monster/Ifari/WakIfari.h"

UWakBTTaskNode_Ifari_Attack::UWakBTTaskNode_Ifari_Attack()
{
    NodeName = TEXT("Ifari_Attack");

    bNotifyTick = true;
    IsAttacking = false;
}

EBTNodeResult::Type UWakBTTaskNode_Ifari_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    AWakIfari* Ifari = Cast<AWakIfari>(OwnerComp.GetAIOwner()->GetPawn());
    if (Ifari != nullptr)
    {
        IsAttacking = true;
        Ifari->MeleeAttack(50.0f);
        Ifari->OnAttackDelegate.AddLambda([this]()->void
            {
                IsAttacking = false;
            });

        return EBTNodeResult::InProgress;
    }

    return EBTNodeResult::Failed;
}

void UWakBTTaskNode_Ifari_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    if (!IsAttacking)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
