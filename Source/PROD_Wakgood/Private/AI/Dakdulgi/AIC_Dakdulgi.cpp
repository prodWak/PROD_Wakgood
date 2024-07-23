// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Dakdulgi/AIC_Dakdulgi.h"

// Behavior
#include "BehaviorTree/BlackboardComponent.h"

const FName AAIC_Dakdulgi::Dakdulgi_HomePosKey(TEXT("HomePos"));
const FName AAIC_Dakdulgi::Dakdulgi_PatrolPosKey(TEXT("PatrolPos"));
const FName AAIC_Dakdulgi::Dakdulgi_TargetKey(TEXT("Target"));

AAIC_Dakdulgi::AAIC_Dakdulgi()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAIC_Dakdulgi::OnPossess(APawn* InPawn)
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