// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_Ifari.h"

#include "BehaviorTree/BlackboardComponent.h"

AWakAIC_Ifari::AWakAIC_Ifari()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWakAIC_Ifari::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_Ifari, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(GetHomePosKey(), InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_Ifari))
		{
			UE_LOG(LogTemp, Error, TEXT("Behavior Tree is not working"));
		}
	}
}
