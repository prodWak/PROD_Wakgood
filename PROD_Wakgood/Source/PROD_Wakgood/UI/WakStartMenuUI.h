// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine.h
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
// Generated
#include "WakStartMenuUI.generated.h"

UCLASS()
class PROD_WAKGOOD_API AWakStartMenuUI : public AHUD
{
	GENERATED_BODY()
	
public:
	AWakStartMenuUI();
	
protected:
	virtual void BeginPlay() override;

public:
	void BindAnyKey();
	void AnyKeyPressed();
	void RemoveStartMenuUI();

protected:
	UPROPERTY(EditAnywhere, Category = "MenuUI")
	TSubclassOf<UUserWidget> StartMenuClass;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> StartMenuWidget;
	
	UPROPERTY()
	TObjectPtr<APlayerController> StartMenuController;
};
