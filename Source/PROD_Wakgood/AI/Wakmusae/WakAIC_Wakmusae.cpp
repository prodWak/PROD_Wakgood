// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_Wakmusae.h"

// Behavior
#include "BehaviorTree/BlackboardComponent.h"

#include "PROD_Wakgood/Character/Monster/Wakmusae/WakWakmusae.h"

const FName AWakAIC_Wakmusae::Wakmusae_HomePosKey(TEXT("Wakmusae_HomePos"));
const FName AWakAIC_Wakmusae::Wakmusae_PatrolPosKey(TEXT("Wakmusae_PatrolPos"));
const FName AWakAIC_Wakmusae::Wakmusae_TargetKey(TEXT("Wakmusae_Target"));

AWakAIC_Wakmusae::AWakAIC_Wakmusae()
{
	PrimaryActorTick.bCanEverTick = true;

	IsDetectPlayer = false;
}

void AWakAIC_Wakmusae::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Test
	if (OwningPawn != nullptr && !OwningPawn->IsDetectPlayer())
	{
		OwningPawn->WalkToward(0.5f);
	}
}

void AWakAIC_Wakmusae::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwningPawn = Cast<AWakWakmusae>(InPawn);

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
