// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WakMainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Game Instance")
	FName LastLocationName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Game Instance")
	FVector LastLocationVector;

	UFUNCTION(BlueprintCallable, Category="Game Instance")
	void SetPlayerLastLocation(int32 LocationIndex);
	
	FORCEINLINE FName GetPlayerLastLocationName() const { return LastLocationName; };
	FORCEINLINE FVector GetPlayerLastLocationVector() const { return LastLocationVector; };
};
