// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTaskNode_Attack.h"

#include "PROD_Wakgood/AI/Dakdulgi/WakAIC_Dakdulgi.h"
#include "PROD_Wakgood/Character/Monster/Dakdulgi/WakDakdulgi.h"

UWakBTTaskNode_Attack::UWakBTTaskNode_Attack()
{
	NodeName = TEXT("Dakdulgi_Attack");

	// bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UWakBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AWakDakdulgi* Dakdulgi = Cast<AWakDakdulgi>(OwnerComp.GetAIOwner()->GetPawn());
	if (Dakdulgi != nullptr)
	{
		// For now, the attack function is called directly, but it needs to be changed to the calling method by animation notify.
		IsAttacking = true;
		Dakdulgi->MeleeAttack(50.0f);
		Dakdulgi->OnAttackDelegate.AddLambda([this]()->void
			{
			IsAttacking = false;
			});

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

//void UWakBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
//
//	if (!IsAttacking)
//	{
//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//	}
//}
