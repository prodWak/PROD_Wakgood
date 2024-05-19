// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionBase.h"
#include "WorldPortal.generated.h"

UCLASS()
class PROD_WAKGOOD_API AWorldPortal : public AInteractionBase
{
	GENERATED_BODY()

	AWorldPortal();
	
	virtual void InteractionWithMe(AActor* target) override;

private:
	UPROPERTY(EditAnywhere)
	FName TransferLevelName;

	UPROPERTY(EditAnywhere)
	FString TransferGameMode;
};