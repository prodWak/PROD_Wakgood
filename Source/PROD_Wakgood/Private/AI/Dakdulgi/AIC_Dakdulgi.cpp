// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Dakdulgi/AIC_Dakdulgi.h"

// Owning Pawn
#include "Character/Monster/Dakdulgi/Wakgood_Dakdulgi.h"

// Kismet
#include "Kismet/KismetMathLibrary.h"

AAIC_Dakdulgi::AAIC_Dakdulgi()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIC_Dakdulgi::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TargetPawn != nullptr)
	{
		Chase();
	}
}

void AAIC_Dakdulgi::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwningDulgi = Cast<AWakgood_Dakdulgi>(InPawn);
}

void AAIC_Dakdulgi::Chase()
{
	if (OwningDulgi != nullptr && TargetPawn != nullptr)
	{
		FVector Start = OwningDulgi->GetActorLocation();
		FVector End = TargetPawn->GetActorLocation();

		UE_LOG(LogTemp, Warning, TEXT("x : %lf, y : %lf, z : %lf"),
			Start.X, Start.Y, Start.Z);

		UE_LOG(LogTemp, Warning, TEXT("x : %lf, y : %lf, z : %lf"),
			End.X, End.Y, End.Z);

		FRotator Result = UKismetMathLibrary::FindLookAtRotation(Start, End);

		OwningDulgi->MoveToward(Result.Vector());
	}
}

void AAIC_Dakdulgi::SetTargetPawn(APawn* Target)
{
	if (TargetPawn != nullptr) { return; }

	if (::IsValid(Target) && TargetPawn == nullptr)
	{
		TargetPawn = Target;
		UE_LOG(LogTemp, Warning, TEXT("Success : %s"), *TargetPawn->GetName());
	}
}

void AAIC_Dakdulgi::InitTargetPawn()
{
	TargetPawn = nullptr;
}
