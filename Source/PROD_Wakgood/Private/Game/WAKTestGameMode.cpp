// Copyright Epic Games, Inc. All Rights Reserved.

#include "..\..\Public\Game\WAKTestGameMode.h"
#include "..\..\Public\Character\WAKTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWAKTestGameMode::AWAKTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
