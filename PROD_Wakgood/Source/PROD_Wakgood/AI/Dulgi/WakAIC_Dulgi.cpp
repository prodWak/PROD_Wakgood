// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_Dulgi.h"

// Behavior
#include "BehaviorTree/BlackboardComponent.h"

#include "PROD_Wakgood/Character/Monster/Dulgi/WakDulgi.h"

const FName AWakAIC_Dulgi::Dulgi_TargetKey(TEXT("Dulgi_Target"));

AWakAIC_Dulgi::AWakAIC_Dulgi()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWakAIC_Dulgi::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (OwningPawn != nullptr && !OwningPawn->GetIsDetectPlayer())
	{
		OwningPawn->WalkForward(0.5f);
	}
}

void AWakAIC_Dulgi::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwningPawn = Cast<AWakDulgi>(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_Dulgi, BLACKBOARD))
	{
		if (!RunBehaviorTree(BT_Dulgi))
		{
			UE_LOG(LogTemp, Error, TEXT("Behavior Tree is not working"));
		}
	}
}
