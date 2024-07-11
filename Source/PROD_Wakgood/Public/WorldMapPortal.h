// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionBase.h"
#include "WorldMapPortal.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWorldMapPortal : public AInteractionBase
{
	GENERATED_BODY()

	AWorldMapPortal();

	virtual void InteractionWithMe(AActor* target) override;

private:
	UPROPERTY(EditAnywhere, Category="Game Instance")
	int32 PlayerLastLocationIndex;

	UPROPERTY(EditAnywhere, Category="Game Instance")
	FName LocationName;

};
