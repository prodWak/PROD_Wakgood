// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine.h
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
// Generated
#include "GameModeMenuUI.generated.h"

UCLASS()
class PROD_WAKGOOD_API AGameModeMenuUI : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameModeMenuUI();

public:
	void SwitchToLoadingScreen();
	void SwitchToMainMenuUI();
};
