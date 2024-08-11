// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTDecorator_Chimpanzee_IsInAttackRange.h"

#include "PROD_Wakgood/AI/Chimpanzee/WakAIC_Chimpanzee.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTDecorator_Chimpanzee_IsInAttackRange::UWakBTDecorator_Chimpanzee_IsInAttackRange()
{
	NodeName = TEXT("Chimpanzee_IsInAttackRange");

	AttackRadius = 200.0f;
}

bool UWakBTDecorator_Chimpanzee_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AWakAIC_Chimpanzee::Chimpanzee_TargetKey));
		if (Target != nullptr)
		{
			bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRadius);
			return bResult;
		}
	}

	return false;
}
