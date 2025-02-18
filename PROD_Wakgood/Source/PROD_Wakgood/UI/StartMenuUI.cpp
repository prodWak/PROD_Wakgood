// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StartMenuUI.h"
// Object or Engine.h
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
// Widget
#include "Blueprint/UserWidget.h"
// Controller
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
// Class.h
#include "GameModeMenuUI.h"

AStartMenuUI::AStartMenuUI()
	: StartMenuWidget(nullptr), StartMenuController(nullptr)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> StartMenuUI(TEXT("/Game/UI/WBP_StartMenu"));
	if (StartMenuUI.Succeeded())
		StartMenuClass = StartMenuUI.Class;
}

void AStartMenuUI::BeginPlay()
{
	Super::BeginPlay();

	if (StartMenuClass)
	{
		StartMenuWidget = CreateWidget<UUserWidget>(GetWorld(), StartMenuClass);

		if (StartMenuWidget)
		{
			StartMenuWidget->AddToViewport();
			StartMenuWidget->SetFocus();

			// Player's Menu Controller
			StartMenuController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (StartMenuController)
			{
				FInputModeGameAndUI InputMode;
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
				StartMenuController->SetInputMode(InputMode);
				StartMenuController->bShowMouseCursor = true;

				// Delay time for prepare to title logo
				FTimerHandle DelayStartMenuUI;
				GetWorld()->GetTimerManager().SetTimer
				(
					DelayStartMenuUI,
					this,
					&ThisClass::BindAnyKey,
					2.0f, // Temporary
					false
				);
			}
		}
	}
}

void AStartMenuUI::BindAnyKey()
{
	// Setup Input Component
	if (StartMenuController)
	{
		StartMenuController->InputComponent->BindKey
		(
			EKeys::AnyKey,
			IE_Pressed,
			this,
			&ThisClass::AnyKeyPressed
		);
	}
}

void AStartMenuUI::AnyKeyPressed()
{
	UE_LOG(LogTemp, Display, TEXT("Any key pressed"));

	if (StartMenuController != nullptr)
	{
		StartMenuController->InputComponent = nullptr;
		StartMenuController = nullptr;

		// Delay time for remove StartMenuUI
		FTimerHandle DelayRemoveStartMenuUI;
		GetWorld()->GetTimerManager().SetTimer
		(
			DelayRemoveStartMenuUI,
			this,
			&ThisClass::RemoveStartMenuUI,
			2.0f,
			false
		);
	}

	// Change HUD
	if (GetWorld())
	{
		auto* ChangeHUD = Cast<AGameModeMenuUI>(GetWorld()->GetAuthGameMode());
		if (ChangeHUD)
		{
			// Delay time for SwitchToMainMenuUI
			FTimerHandle DelaySwitchToMainMenuUI;
			GetWorld()->GetTimerManager().SetTimer
			(
				DelaySwitchToMainMenuUI,
				ChangeHUD,
				&AGameModeMenuUI::SwitchToMainMenuUI,
				3.5f,
				false
			);
		}
	}
}

// void AStartMenuUI::AnyKeyPressedToSwitchToLoadingScreen()
// {
// 	// LOG
// 	UE_LOG(LogTemp, Warning, TEXT("Any Key Pressed !"));
//
// 	if (StartMenuController != nullptr)
// 	{
// 		StartMenuController = nullptr;
// 		
// 		// delay time for remove StartMenuUI
// 		FTimerHandle DelayRemoveStartMenuUI;
// 		GetWorld()->GetTimerManager().SetTimer
// 		(
// 			DelayRemoveStartMenuUI,
// 			this,
// 			&ThisClass::RemoveStartMenuUI,
// 			2.0f,
// 			false
// 		);
// 	}
//
// 	// change HUD
// 	if (GetWorld())
// 	{
// 		AGameModeMenuUI* ChangeHUD = Cast<AGameModeMenuUI>(GetWorld()->GetAuthGameMode());
// 		if (ChangeHUD)
// 		{
// 			// delay time for SwitchToLoadingScreen
// 			FTimerHandle DelaySwitchToLoadingScreen;
// 			GetWorld()->GetTimerManager().SetTimer
// 			(
// 				DelaySwitchToLoadingScreen,
// 				ChangeHUD,
// 				&AGameModeMenuUI::SwitchToLoadingScreen,
// 				2.1f, // Temporary
// 				false
// 			);
// 		}
// 	}
// }

void AStartMenuUI::RemoveStartMenuUI()
{
	if (StartMenuWidget)
	{
		StartMenuWidget->RemoveFromParent();
		StartMenuWidget = nullptr;

		// LOG
		if (StartMenuWidget == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Start Menu Removed !"));
		}
	}
}
