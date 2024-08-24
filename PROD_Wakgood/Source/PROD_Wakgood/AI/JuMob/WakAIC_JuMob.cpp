// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_JuMob.h"

#include "BehaviorTree/BlackboardComponent.h"

AWakAIC_JuMob::AWakAIC_JuMob()
	: IsDetectTargetKey(TEXT("IsDetectTarget"))
{
}

void AWakAIC_JuMob::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_JuMob, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(GetHomePosKey(), InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_JuMob))
		{
			UE_LOG(LogTemp, Error, TEXT("BehaivorTree is not working"));
		}
	}
}
