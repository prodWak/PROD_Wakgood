// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine.h
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
// Generated
#include "WakMenuUIGameMode.generated.h"

UCLASS()
class PROD_WAKGOOD_API AWakMenuUIGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWakMenuUIGameMode();

public:
	void SwitchToMainMenuUI();
};
