// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WakDialogueDataTable.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakDialogueDataTable : public UDataTable
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct PROD_WAKGOOD_API FDialogueStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString NPCName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 Index;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Text;
};