// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMap.h"
#include "PROD_WakgoodCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWorldMap::AWorldMap()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/PROD_Wakgood.PROD_WakgoodCharacter_WorldMap"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}