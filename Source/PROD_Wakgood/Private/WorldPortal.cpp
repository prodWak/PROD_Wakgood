// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldPortal.h"
#include "Kismet/GameplayStatics.h"

AWorldPortal::AWorldPortal()
{
	TransferLevelName = TEXT("World1");
	TransferGameMode = TEXT("GM_Debug");
}

void AWorldPortal::InteractionWithMe(AActor* target)
{
	Super::InteractionWithMe(target);
	
	UGameplayStatics::OpenLevel(this, TransferLevelName, false, TransferGameMode);
}