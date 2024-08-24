// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_JuMob_BusterCall.h"

#include "PROD_Wakgood/AI/JuMob/WakAIC_JuMob.h"
#include "PROD_Wakgood/Character/Monster/JuMob/WakJuMob.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTTask_JuMob_BusterCall::UWakBTTask_JuMob_BusterCall()
{
	NodeName = TEXT("JuMob_BusterCall");
}

EBTNodeResult::Type UWakBTTask_JuMob_BusterCall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn())
	{
		if (AWakJuMob* AIOwner = Cast<AWakJuMob>(ControllingPawn))
		{
			AIOwner->CallAllJuMob();
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
