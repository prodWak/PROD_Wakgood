// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIC_Base.h"

AAIC_Base::AAIC_Base()
{
	
}

void AAIC_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("OnPossess"));
}

void AAIC_Base::SetTargetPawn(APawn* Target)
{
	if (TargetPawn != nullptr)
	{
		return;
	}

	if (::IsValid(Target) && TargetPawn == nullptr)
	{
		TargetPawn = Target;

		if (TargetPawn != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Success Setting : %s"), *TargetPawn->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed Setting"))
		}
	}
}
