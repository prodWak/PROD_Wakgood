// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTaskNode_BatDan_Attack.h"

#include "PROD_Wakgood/AI/BatDan/WakAIC_BatDan.h"
#include "PROD_Wakgood/Character/Monster/BatDan/WakBatDan.h"


UWakBTTaskNode_BatDan_Attack::UWakBTTaskNode_BatDan_Attack()
{
	NodeName = TEXT("BatDan_Attack");
	// bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UWakBTTaskNode_BatDan_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	AWakBatDan* BatDan = Cast<AWakBatDan>(OwnerComp.GetAIOwner()->GetPawn());
	if (BatDan != nullptr)
	{
		// For now, the attack function is called directly, but it needs to be changed to the calling method by animation notify.
		IsAttacking = true;
		BatDan->Attack();
		BatDan->OnAttackDelegate.AddLambda([this]()->void
			{
				IsAttacking = false;
			});

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
//
//void UWakBTTaskNode_BatDan_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
//
//	if (!IsAttacking)
//	{
//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//	}
//}
