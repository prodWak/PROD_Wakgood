// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Dakdulgi/AIC_Dakdulgi.h"

// Owning Pawn
#include "Character/Monster/Dakdulgi/Wakgood_Dakdulgi.h"

// Kismet
#include "Kismet/KismetMathLibrary.h"

// Navigation
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Behavior
#include "BehaviorTree/BlackboardComponent.h"

const FName AAIC_Dakdulgi::HomePosKey(TEXT("HomePos"));
const FName AAIC_Dakdulgi::PatrolPosKey(TEXT("PatrolPos"));

AAIC_Dakdulgi::AAIC_Dakdulgi()
{
	PrimaryActorTick.bCanEverTick = false;

	RepeatInterval = 3.0f;
}

void AAIC_Dakdulgi::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_Dakdulgi, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_Dakdulgi))
		{
			UE_LOG(LogTemp, Error, TEXT("Can't Run BehaviorTree"));
		}
	}

	OwningDulgi = Cast<AWakgood_Dakdulgi>(InPawn);

	GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AAIC_Dakdulgi::OnRepeatTimer, RepeatInterval, true);
}

void AAIC_Dakdulgi::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void AAIC_Dakdulgi::OnRepeatTimer()
{
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSys != nullptr)
	{
		FNavLocation NextLocation;

		if (NavSys->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
		}
	}
}

void AAIC_Dakdulgi::Chase()
{
	if (OwningDulgi != nullptr && TargetPawn != nullptr)
	{
		FVector Start = OwningDulgi->GetActorLocation();
		FVector End = TargetPawn->GetActorLocation();

		FRotator Result = UKismetMathLibrary::FindLookAtRotation(Start, End);

		OwningDulgi->MoveToward(Result.Vector());
	}
	
	// Attack Logic...
}

void AAIC_Dakdulgi::SetTargetPawn(APawn* Target)
{
	if (TargetPawn != nullptr) { return; }

	if (::IsValid(Target) && TargetPawn == nullptr)
	{
		TargetPawn = Target;
	}
}

void AAIC_Dakdulgi::InitTargetPawn()
{
	TargetPawn = nullptr;
}
