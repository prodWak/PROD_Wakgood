// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_PoopDog_BusterCall.h"

#include "PROD_Wakgood/AI/PoopDog/WakAIC_PoopDog.h"
#include "PROD_Wakgood/Character/Monster/PoopDog/WakPoopDog.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTTask_PoopDog_BusterCall::UWakBTTask_PoopDog_BusterCall()
{
	NodeName = TEXT("PoopDog_BusterCall");
}

EBTNodeResult::Type UWakBTTask_PoopDog_BusterCall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakPoopDog* AIOwner = Cast<AWakPoopDog>(ControllingPawn);
		if (AIOwner != nullptr)
		{
			AIOwner->BusterCall();
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
