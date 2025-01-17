// Fill out your copyright notice in the Description page of Project Settings.


#include "WakWorldMapPortal.h"

#include "Character/WakCharacterBase.h"
#include "PROD_Wakgood/Game/WakMainGameInstance.h"
#include "Kismet/GameplayStatics.h"

AWorldMapPortal::AWorldMapPortal()
{
	LocationName = TEXT("MAP_Debug");
}

void AWorldMapPortal::Interaction(AActor* target)
{
	Super::Interaction(target);
	UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetWorld()->GetGameInstance());
	AWakCharacterBase* targetCharacter = Cast<AWakCharacterBase>(target);
	if (GameInstance)
	{
		UGameplayStatics::OpenLevel(this, LocationName, false);
		targetCharacter->SetActorLocation(GameInstance->GetPlayerLastLocationVector());
	}
}
