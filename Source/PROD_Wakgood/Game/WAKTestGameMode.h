// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WAKTestGameMode.generated.h"

class UCharacterClassInfo;

UCLASS(minimalapi)
class AWAKTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWAKTestGameMode();
	UPROPERTY(EditDefaultsOnly, Category= "Character Class Info")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};



