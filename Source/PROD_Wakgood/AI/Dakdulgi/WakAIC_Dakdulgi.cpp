// Fill out your copyright notice in the Description page of Project Settings.

#include "WakAIC_Dakdulgi.h"

// Behavior
#include "BehaviorTree/BlackboardComponent.h"

const FName AWakAIC_Dakdulgi::Dakdulgi_HomePosKey(TEXT("HomePos"));
const FName AWakAIC_Dakdulgi::Dakdulgi_PatrolPosKey(TEXT("PatrolPos"));
const FName AWakAIC_Dakdulgi::Dakdulgi_TargetKey(TEXT("Target"));

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
		BLACKBOARD->SetValueAsVector(Dakdulgi_HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_Dakdulgi))
		{
			UE_LOG(LogTemp, Error, TEXT("Can't Run BehaviorTree"));
		}
	}
}