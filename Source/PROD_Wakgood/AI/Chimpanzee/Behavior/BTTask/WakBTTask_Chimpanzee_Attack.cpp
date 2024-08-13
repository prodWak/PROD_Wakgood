// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_Chimpanzee_Attack.h"

#include "PROD_Wakgood/AI/Chimpanzee/WakAIC_Chimpanzee.h"
#include "PROD_Wakgood/Character/Monster/Chimpanzee/WakChimpanzee.h"

UWakBTTask_Chimpanzee_Attack::UWakBTTask_Chimpanzee_Attack()
{
	NodeName = TEXT("Chimpanzee_Attack");

	// bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UWakBTTask_Chimpanzee_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AWakChimpanzee* Chimpanzee = Cast<AWakChimpanzee>(OwnerComp.GetAIOwner()->GetPawn());
	if (Chimpanzee != nullptr)
	{
		IsAttacking = true;
		Chimpanzee->MeleeAttack(50.0f);
		Chimpanzee->OnAttackDelegate.AddLambda([this]()->void
			{
				IsAttacking = false;
			});

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

//void UWakBTTask_Chimpanzee_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
//
//	if (!IsAttacking)
//	{
//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//	}
//}
