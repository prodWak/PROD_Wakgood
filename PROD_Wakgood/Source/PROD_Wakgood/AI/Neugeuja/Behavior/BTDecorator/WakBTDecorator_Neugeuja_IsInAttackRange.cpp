// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTDecorator_Neugeuja_IsInAttackRange.h"

#include "PROD_Wakgood/AI/Neugeuja/WakAIC_Neugeuja.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "PROD_Wakgood/Character/Monster/Neugeuja/WakNeugeuja.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTDecorator_Neugeuja_IsInAttackRange::UWakBTDecorator_Neugeuja_IsInAttackRange()
{
	NodeName = TEXT("Neugeuja_IsInAttackRange");
	AttackRadius = 200.0f;
}

bool UWakBTDecorator_Neugeuja_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_Neugeuja* AIController = Cast<AWakAIC_Neugeuja>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));
		if (AIController != nullptr)
		{
			AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AIController->GetTargetKey()));
			if (Target != nullptr)
			{
				bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRadius);
				return bResult;
			}
		}
	}

	return false;
}
