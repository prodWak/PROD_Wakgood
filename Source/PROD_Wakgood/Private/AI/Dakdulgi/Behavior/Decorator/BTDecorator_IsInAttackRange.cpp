// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Dakdulgi/Behavior/Decorator/BTDecorator_IsInAttackRange.h"

#include "AI/Dakdulgi/AIC_Dakdulgi.h"
#include "Character/Player/Wakgood_DebugPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");

	AttackRadius = 200.0f;
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakgood_DebugPlayer* Target = Cast<AWakgood_DebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AAIC_Dakdulgi::TargetKey));
		if (Target != nullptr)
		{
			bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRadius);
			return bResult;
		}
	}

	return false;
}
