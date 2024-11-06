// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game\WAKTestGameMode.h"
#include "Character\WAKTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWAKTestGameMode::AWAKTestGameMode()
{
	// set default pawn class to our Blueprinted character
	/*
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/BP_WAKTestCharacter.BP_WAKTestCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	*/

		
}
