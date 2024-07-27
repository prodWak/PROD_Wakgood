// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTDecorator_Dakdulbi_IsInAttackRange.h"

#include "PROD_Wakgood/AI/Dakdulgi/WakAIC_Dakdulgi.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTDecorator_Dakdulbi_IsInAttackRange::UWakBTDecorator_Dakdulbi_IsInAttackRange()
{
	NodeName = TEXT("Dakdulgi_CanAttack");

	AttackRadius = 200.0f;
}

bool UWakBTDecorator_Dakdulbi_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AWakAIC_Dakdulgi::Dakdulgi_TargetKey));
		if (Target != nullptr)
		{
			bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRadius);
			return bResult;
		}
	}

	return false;
}
