// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTaskNode_Lani_Attack.h"

#include "PROD_Wakgood/AI/Lani/WakAIC_Lani.h"
#include "PROD_Wakgood/Character/Monster/Lani/WakLani.h"

UWakBTTaskNode_Lani_Attack::UWakBTTaskNode_Lani_Attack()
{
	NodeName = TEXT("Lani_Attack");
	IsAttacking = false;
}

EBTNodeResult::Type UWakBTTaskNode_Lani_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    AWakLani* Lani = Cast<AWakLani>(OwnerComp.GetAIOwner()->GetPawn());
    if (Lani != nullptr)
    {
        IsAttacking = true;
        Lani->MeleeAttack(50.0f);
        Lani->OnAttackDelegate.AddLambda([this]()->void
            {
                IsAttacking = false;
            });

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}