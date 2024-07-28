// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTDecorator_Wakmusae_IsInAttackRange.h"

#include "PROD_Wakgood/AI/Wakmusae/WakAIC_Wakmusae.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTDecorator_Wakmusae_IsInAttackRange::UWakBTDecorator_Wakmusae_IsInAttackRange()
{
    NodeName = TEXT("Wakmusae_CanAttack");

    AttackRadius = 250.0f;
}

bool UWakBTDecorator_Wakmusae_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AWakAIC_Wakmusae::Wakmusae_TargetKey));
		if (Target != nullptr)
		{
			bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRadius);
			return bResult;
		}
	}

	return false;
}
