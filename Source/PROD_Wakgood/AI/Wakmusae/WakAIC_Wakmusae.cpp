// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_Wakmusae.h"

// Behavior
#include "BehaviorTree/BlackboardComponent.h"

#include "PROD_Wakgood/Character/Monster/Wakmusae/WakWakmusae.h"

const FName AWakAIC_Wakmusae::Wakmusae_TargetKey(TEXT("Wakmusae_Target"));

AWakAIC_Wakmusae::AWakAIC_Wakmusae()
{
	PrimaryActorTick.bCanEverTick = true;

	IsDetectPlayer = false;
}

void AWakAIC_Wakmusae::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (OwningPawn != nullptr && !OwningPawn->GetIsDetectPlayer())
	{
		OwningPawn->WalkForward(0.5f);
	}
}

void AWakAIC_Wakmusae::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwningPawn = Cast<AWakWakmusae>(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_Wakmusae, BLACKBOARD))
	{
		if (!RunBehaviorTree(BT_Wakmusae))
		{
			UE_LOG(LogTemp, Error, TEXT("Behavior Tree is not working"));
		}
	}
}
