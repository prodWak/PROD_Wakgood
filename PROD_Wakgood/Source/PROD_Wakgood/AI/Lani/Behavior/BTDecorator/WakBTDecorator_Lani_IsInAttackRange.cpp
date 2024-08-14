// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTDecorator_Lani_IsInAttackRange.h"

#include "PROD_Wakgood/AI/Lani/WakAIC_Lani.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

UWakBTDecorator_Lani_IsInAttackRange::UWakBTDecorator_Lani_IsInAttackRange()
{
	NodeName = TEXT("Lani_IsInAttackRange");
	AttackRadius = 200.0f;
}

bool UWakBTDecorator_Lani_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_Lani* AIController = Cast<AWakAIC_Lani>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));
		AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AIController->GetTargetKey()));
		if (Target != nullptr)
		{
			bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRadius);
			return bResult;
		}
	}

	return false;
}
