// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTaskNode_Dulgi_Attack.h"

#include "PROD_Wakgood/AI/Dulgi/WakAIC_Dulgi.h"
#include "PROD_Wakgood/Character/Monster/Dulgi/WakDulgi.h"

UWakBTTaskNode_Dulgi_Attack::UWakBTTaskNode_Dulgi_Attack()
{
    NodeName = TEXT("Dulgi_Attack");

    // bNotifyTick = true;
    IsAttacking = false;
}

EBTNodeResult::Type UWakBTTaskNode_Dulgi_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AWakDulgi* Dulgi = Cast<AWakDulgi>(OwnerComp.GetAIOwner()->GetPawn());
	if (Dulgi != nullptr)
	{
		// For now, the attack function is called directly, but it needs to be changed to the calling method by animation notify.
		IsAttacking = true;
		Dulgi->Attack();
		Dulgi->OnAttackDelegate.AddLambda([this]()->void
			{
				IsAttacking = false;
			});

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

//void UWakBTTaskNode_Dulgi_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
//
//	if (!IsAttacking)
//	{
//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//	}
//}
