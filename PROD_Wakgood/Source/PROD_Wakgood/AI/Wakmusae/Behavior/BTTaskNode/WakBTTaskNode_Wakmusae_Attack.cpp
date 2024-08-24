// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTaskNode_Wakmusae_Attack.h"

#include "PROD_Wakgood/AI/Wakmusae/WakAIC_Wakmusae.h"
#include "PROD_Wakgood/Character/Monster/Wakmusae/WakWakmusae.h"

UWakBTTaskNode_Wakmusae_Attack::UWakBTTaskNode_Wakmusae_Attack()
{
	NodeName = TEXT("Wakmusae_Attack");

	// bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UWakBTTaskNode_Wakmusae_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AWakWakmusae* Wakmusae = Cast<AWakWakmusae>(OwnerComp.GetAIOwner()->GetPawn());
	if (Wakmusae != nullptr)
	{
		// For now, the attack function is called directly, but it needs to be changed to the calling method by animation notify.
		IsAttacking = true;
		Wakmusae->OnAttackDelegate.AddLambda([this]()->void
			{
				IsAttacking = false;
			});

		Wakmusae->Attack();

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

//void UWakBTTaskNode_Wakmusae_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
//
//	if (!IsAttacking)
//	{
//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//	}
//}
