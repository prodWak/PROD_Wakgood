// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_BacteriaDan.h"

#include "BehaviorTree/BlackboardComponent.h"

AWakAIC_BacteriaDan::AWakAIC_BacteriaDan()
	:BacteriaDan_HomePosKey(TEXT("BacteriaDan_HomePos"))
{
}

void AWakAIC_BacteriaDan::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_BacteriaDan, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(BacteriaDan_HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_BacteriaDan))
		{
			UE_LOG(LogTemp, Error, TEXT("Behavior Tree is not working"));
		}
	}
}
