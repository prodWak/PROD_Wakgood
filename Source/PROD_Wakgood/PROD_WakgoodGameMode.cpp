// Copyright Epic Games, Inc. All Rights Reserved.

#include "PROD_WakgoodGameMode.h"
#include "PROD_WakgoodCharacter.h"
#include "UObject/ConstructorHelpers.h"

APROD_WakgoodGameMode::APROD_WakgoodGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
