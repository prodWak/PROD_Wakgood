// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine.h
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
// Generated
#include "MainMenuUI.generated.h"

// Forward Declaration
class UButton;

UCLASS()
class PROD_WAKGOOD_API AMainMenuUI : public AHUD
{
	GENERATED_BODY()
	
public:
	AMainMenuUI();

protected:
	virtual void BeginPlay() override;
	
public:
	void InitInput();
	void ButtonFocus(int32 buttonIndex);
	void ProcessW();
	void ProcessS();
	// void ProcessA();
	// void ProcessD();
	void ProcessJ();

	UFUNCTION()
	void OnStoryButtonClicked();
	
	UFUNCTION()
	void SetHoveredButton(UButton* hoveredButton, bool bIsHovered);

protected:
	UPROPERTY(EditAnywhere, Category = "MenuUI")
	TSubclassOf<UUserWidget> MainMenuClass;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenuWidget;
	
	UPROPERTY()
	TObjectPtr<APlayerController> MainMenuController;

	UPROPERTY()
	TArray<TObjectPtr<UButton>> MainMenuButtons;
	
	int32 CurrentButtonIndex = 0;
	int32 TargetButtonIndex = 0;
};
