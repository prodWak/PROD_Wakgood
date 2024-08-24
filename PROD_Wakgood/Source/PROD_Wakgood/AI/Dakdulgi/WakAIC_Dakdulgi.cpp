// Fill out your copyright notice in the Description page of Project Settings.

#include "WakAIC_Dakdulgi.h"

// Behavior
#include "BehaviorTree/BlackboardComponent.h"

AWakAIC_Dakdulgi::AWakAIC_Dakdulgi()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWakAIC_Dakdulgi::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_Dakdulgi, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(GetHomePosKey(), InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_Dakdulgi))
		{
			UE_LOG(LogTemp, Error, TEXT("Behavior Tree is not working"));
		}
	}
}