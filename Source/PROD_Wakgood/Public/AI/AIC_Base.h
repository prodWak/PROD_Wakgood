// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_Base.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AAIC_Base : public AAIController
{
	GENERATED_BODY()

	TObjectPtr<APawn> TargetPawn;

public:
	AAIC_Base();

	virtual void OnPossess(APawn* InPawn) override;

	void SetTargetPawn(APawn* Target);
	
};
