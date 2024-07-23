// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_Wakmusae.h"

// Behavior
#include "BehaviorTree/BlackboardComponent.h"

const FName AWakAIC_Wakmusae::Wakmusae_HomePosKey(TEXT("HomePos"));
const FName AWakAIC_Wakmusae::Wakmusae_PatrolPosKey(TEXT("PatrolPos"));
const FName AWakAIC_Wakmusae::Wakmusae_TargetKey(TEXT("Target"));

AWakAIC_Wakmusae::AWakAIC_Wakmusae()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWakAIC_Wakmusae::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_Wakmusae, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(Wakmusae_HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_Wakmusae))
		{
			UE_LOG(LogTemp, Error, TEXT("Can't Run BehaviorTree"));
		}
	}
}
