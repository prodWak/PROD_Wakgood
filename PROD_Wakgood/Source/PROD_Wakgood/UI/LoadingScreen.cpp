// Fill out your copyright notice in the Description page of Project Settings.

// Engine.h
#include "UI/LoadingScreen.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
// Class.h
#include "GameModeMenuUI.h"

ALoadingScreen::ALoadingScreen()
	: LoadingScreenWidget(nullptr)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> LoadingScreen(TEXT("/Game/UI/WBP_LoadingScreen"));
	if (LoadingScreen.Succeeded())
	{
		LoadingScreenClass = LoadingScreen.Class;
	}
}

void ALoadingScreen::BeginPlay()
{
	Super::BeginPlay();

	if (LoadingScreenClass)
	{
		LoadingScreenWidget = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenClass);

		if (LoadingScreenWidget)
		{
			LoadingScreenWidget->AddToViewport();

			// delay time
			FTimerHandle DelayLoadingSucceeded;
			GetWorld()->GetTimerManager().SetTimer
			(
				DelayLoadingSucceeded,
				this,
				&ALoadingScreen::RemoveLoadingScreen,
				3.3f, // Temporary
				false
			);
		}
	}

	// change HUD
	if (GetWorld())
	{
		AGameModeMenuUI* ChangeHUD = Cast<AGameModeMenuUI>(GetWorld()->GetAuthGameMode());
		if (ChangeHUD)
		{
			// delay time
			FTimerHandle DelaySwitchToMainMenuUI;
			GetWorld()->GetTimerManager().SetTimer
			(
				DelaySwitchToMainMenuUI,
				ChangeHUD,
				&AGameModeMenuUI::SwitchToMainMenuUI,
				3.5f, // Temporary
				false
			);
		}
	}
}

void ALoadingScreen::RemoveLoadingScreen()
{
	if (LoadingScreenWidget != nullptr)
	{
		LoadingScreenWidget->RemoveFromParent();
		LoadingScreenWidget = nullptr;

		// LOG
		if (LoadingScreenWidget == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Loaded !"))
		}
	}
}