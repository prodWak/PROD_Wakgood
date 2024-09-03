// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "WakDialogueWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* MainTextBox;
	
};
