// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTDecorator_Ifari_IsInAttackRange.h"

#include "PROD_Wakgood/AI/Ifari/WakAIC_Ifari.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTDecorator_Ifari_IsInAttackRange::UWakBTDecorator_Ifari_IsInAttackRange()
{
	NodeName = TEXT("Ifari_IsInAttackRange");
	AttackRadius = 200.0f;
}

bool UWakBTDecorator_Ifari_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AWakAIC_Ifari::Ifari_TargetKey));
		if (Target != nullptr)
		{
			bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRadius);
			return bResult;
		}
	}

	return false;
}
