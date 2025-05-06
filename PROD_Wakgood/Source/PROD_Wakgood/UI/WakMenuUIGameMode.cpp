// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/WakMenuUIGameMode.h"
// Class.h
#include "WakStartMenuUI.h"
#include "WakMainMenuUI.h"


AWakMenuUIGameMode::AWakMenuUIGameMode()
{
	HUDClass = AWakStartMenuUI::StaticClass();
}

void AWakMenuUIGameMode::SwitchToMainMenuUI()
{
	HUDClass = AWakMainMenuUI::StaticClass();
	GetWorld()->GetFirstPlayerController()->ClientSetHUD(AWakMainMenuUI::StaticClass());
}
