// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GameModeMenuUI.h"
// Class.h
#include "StartMEnuUI.h"
#include "LoadingScreen.h"
#include "MainMenuUI.h"


AGameModeMenuUI::AGameModeMenuUI()
{
	HUDClass = AStartMenuUI::StaticClass();
}

void AGameModeMenuUI::SwitchToLoadingScreen()
{
	HUDClass = ALoadingScreen::StaticClass();
	GetWorld()->GetFirstPlayerController()->ClientSetHUD(ALoadingScreen::StaticClass());
}

void AGameModeMenuUI::SwitchToMainMenuUI()
{
	HUDClass = AMainMenuUI::StaticClass();
	GetWorld()->GetFirstPlayerController()->ClientSetHUD(AMainMenuUI::StaticClass());
}
