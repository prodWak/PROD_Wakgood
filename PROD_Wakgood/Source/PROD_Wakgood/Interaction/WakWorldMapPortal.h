// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WakInteractionBase.h"
#include "WakWorldMapPortal.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakWorldMapPortal : public AWakInteractionBase
{
	GENERATED_BODY()

	AWakWorldMapPortal();

	virtual void Interaction(AActor* target) override;

private:
	UPROPERTY(EditAnywhere, Category="Game Instance")
	int32 PlayerLastLocationIndex;

	UPROPERTY(EditAnywhere, Category="Game Instance")
	FName LocationName;

};
