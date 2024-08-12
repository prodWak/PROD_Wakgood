// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_Amoeba_Transformation.h"

#include "PROD_Wakgood/AI/Amoeba/WakAIC_Amoeba.h"
#include "PROD_Wakgood/Character/Monster/Amoeba/WakAmoeba.h"

UWakBTTask_Amoeba_Transformation::UWakBTTask_Amoeba_Transformation()
{
	NodeName = TEXT("Amoeba_Transformation");
}

EBTNodeResult::Type UWakBTTask_Amoeba_Transformation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AWakAmoeba* AIOwner = Cast<AWakAmoeba>(ControllingPawn);
	if (AIOwner != nullptr)
	{
		AIOwner->CheckTransformation();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
