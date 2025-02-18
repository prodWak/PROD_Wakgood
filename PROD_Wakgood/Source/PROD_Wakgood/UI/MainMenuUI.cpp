// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/MainMenuUI.h"
// Object or Engine.h
#include "UObject/ConstructorHelpers.h"
// Widget
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Widget.h"
// Controller
#include "GameFramework/PlayerController.h"
#include "Framework/Application/SlateApplication.h"
#include "Input/Events.h"
#include "Kismet/GameplayStatics.h"

AMainMenuUI::AMainMenuUI()
	: MainMenuWidget(nullptr), MainMenuController(nullptr)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuUI(TEXT("/Game/UI/WBP_MainMenu"));
	if (MainMenuUI.Succeeded())
		MainMenuClass = MainMenuUI.Class;
}

void AMainMenuUI::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport();

		// Player's Menu Controller
		MainMenuController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (MainMenuController)
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(MainMenuWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			MainMenuController->SetInputMode(InputMode);

			if (!MainMenuController->InputComponent)
			{
				MainMenuController->InputComponent = NewObject<UInputComponent>(MainMenuController);
				MainMenuController->InputComponent->RegisterComponent();
			}
		}

		// Buttons Array
		auto* btnStory = Cast<UButton>(MainMenuWidget->GetWidgetFromName(TEXT("btnStory")));
		auto* btnSettings = Cast<UButton>(MainMenuWidget->GetWidgetFromName(TEXT("btnSettings")));
		auto* btnGallery = Cast<UButton>(MainMenuWidget->GetWidgetFromName(TEXT("btnGallery")));
		auto* btnManual = Cast<UButton>(MainMenuWidget->GetWidgetFromName(TEXT("btnManual")));
		auto* btnCredits = Cast<UButton>(MainMenuWidget->GetWidgetFromName(TEXT("btnCredits")));
		MainMenuButtons = {btnStory, btnSettings, btnGallery, btnManual, btnCredits};

		// When clicked
		btnStory->OnClicked.AddDynamic(this, &ThisClass::OnStoryButtonClicked);
		// btnSettings->OnClicked.AddDynamic(this, &ThisClass::OnSettingsButtonClicked); still didnt declare
		// btnGallery->OnClicked.AddDynamic(this, &ThisClass::OnGalleryButtonClicked); still didnt declare
		// btnManual->OnClicked.AddDynamic(this, &ThisClass::OnManualButtonClicked); still didnt declare
		// btnCredits->OnClicked.AddDynamic(this, &ThisClass::OnCreditsButtonClicked); still didnt declare

		if (MainMenuButtons.IsValidIndex(0))
		{
			ButtonFocus(0);
		}

		InitInput();
	}
}


void AMainMenuUI::InitInput()
{
	// Setup Input Component
	if (MainMenuController && MainMenuController->InputComponent)
	{
		MainMenuController->InputComponent->BindKey
			(EKeys::W, IE_Pressed, this, &ThisClass::ProcessW);
		MainMenuController->InputComponent->BindKey
			(EKeys::S, IE_Pressed, this, &ThisClass::ProcessS);
		// MainMenuController->InputComponent->BindKey
		// (EKeys::A, IE_Pressed, this, &ThisClass::ProcessA);
		// MainMenuController->InputComponent->BindKey
		// (EKeys::D, IE_Pressed, this, &ThisClass::ProcessD);
		MainMenuController->InputComponent->BindKey
			(EKeys::J, IE_Pressed, this, &ThisClass::ProcessJ);
	}
}

void AMainMenuUI::ButtonFocus(int32 buttonIndex)
{
	// Get Hovered Button Focus
	if (!MainMenuButtons.IsValidIndex(buttonIndex))
		return;

	if (MainMenuButtons.IsValidIndex(CurrentButtonIndex))
		SetHoveredButton(MainMenuButtons[CurrentButtonIndex], false);

	if (MainMenuButtons[buttonIndex])
	{
		auto* Widget = Cast<UWidget>(MainMenuButtons[buttonIndex]);
		if (Widget)
		{
			Widget->SetFocus();
			CurrentButtonIndex = buttonIndex;
			SetHoveredButton(MainMenuButtons[buttonIndex], true);
		}
	}
}

void AMainMenuUI::ProcessW()
{
	// 0 - StoryMode
	// 1 - Settings
	// 2 - Gallery
	// 3 - Manual
	// 4 - Credits
		// I'll refactor this later if we need.
	
	TargetButtonIndex = -1;

	// UP movement rule
	if (CurrentButtonIndex == 4)
		TargetButtonIndex = 3;
	else if (CurrentButtonIndex == 3)
		TargetButtonIndex = 2;
	else if (CurrentButtonIndex == 2)
		TargetButtonIndex = 1;
	else if (CurrentButtonIndex == 1)
		TargetButtonIndex = 0;
	else if (CurrentButtonIndex == 0)
		TargetButtonIndex = 4;

	if (TargetButtonIndex != -1)
		ButtonFocus(TargetButtonIndex);
}

void AMainMenuUI::ProcessS()
{
	TargetButtonIndex = -1;

	// DOWN movement rule
	if (CurrentButtonIndex == 0)
		TargetButtonIndex = 1;
	else if (CurrentButtonIndex == 1)
		TargetButtonIndex = 2;
	else if (CurrentButtonIndex == 2)
		TargetButtonIndex = 3;
	else if (CurrentButtonIndex == 3)
		TargetButtonIndex = 4;
	else if (CurrentButtonIndex == 4)
		TargetButtonIndex = 0;

	if (TargetButtonIndex != -1)
		ButtonFocus(TargetButtonIndex);
}

// void AMainMenuUI::ProcessA()
// {
// 	TargetButtonIndex = -1;
//
// 	// LEFT movement rule
// 	if (CurrentButtonIndex <= 3 && CurrentButtonIndex != 0)
// 		TargetButtonIndex = 0;
//
// 	if (TargetButtonIndex != -1)
// 		ButtonFocus(TargetButtonIndex);
// }
//
// void AMainMenuUI::ProcessD()
// {
// 	TargetButtonIndex = -1;
//
// 	// RIGHT movement rule
// 	if (CurrentButtonIndex == 0)
// 		TargetButtonIndex = 1;
//
// 	if (TargetButtonIndex != -1)
// 		ButtonFocus(TargetButtonIndex);
// }

void AMainMenuUI::ProcessJ()
{
	TSharedPtr<SWidget> FocusedWidget = FSlateApplication::Get().GetUserFocusedWidget(0);
	if (FocusedWidget.IsValid())
	{
		FKeyEvent KeyEvent
		(
			EKeys::Enter,
			FModifierKeysState(),
			0,
			false,
			0,
			0
		);

		FSlateApplication::Get().ProcessKeyDownEvent(KeyEvent);
		FSlateApplication::Get().ProcessKeyUpEvent(KeyEvent);
	}
}

void AMainMenuUI::OnStoryButtonClicked()
{
	// Need load assets and change GameModeBase, HUD, etc...blah blah
		// I'm waiting :)
	UE_LOG(LogTemp, Warning, TEXT("StoryButton Clicked !"));

	MainMenuController->InputComponent = nullptr;
	MainMenuController = nullptr;
}

void AMainMenuUI::SetHoveredButton(UButton* hoveredButton, bool bIsHovered)
{
	if (!hoveredButton)
		return;

	if (bIsHovered)
		hoveredButton->OnHovered.Broadcast();
	else
		hoveredButton->OnUnhovered.Broadcast();
}
