// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_JuMob_Attack.h"

#include "PROD_Wakgood/AI/JuMob/WakAIC_JuMob.h"
#include "PROD_Wakgood/Character/Monster/JuMob/WakJuMob.h"

UWakBTTask_JuMob_Attack::UWakBTTask_JuMob_Attack()
{
	NodeName = TEXT("JuMob_Attack");
	IsAttacking = false;
}

EBTNodeResult::Type UWakBTTask_JuMob_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakJuMob* AIOwner = Cast<AWakJuMob>(ControllingPawn);
		if (AIOwner != nullptr)
		{
			IsAttacking = true;
			AIOwner->OnAttackDelegate.AddLambda([this]()->void
				{
					IsAttacking = false;
				});

			// Need Animation
			// 

			AIOwner->MeleeAttack(50.0f);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
