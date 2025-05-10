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
	const UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetWorld()->GetGameInstance());
	AWakCharacterBase* TargetCharacter = Cast<AWakCharacterBase>(target);
	
	if (!GameInstance)
	{
		return;
	}

	UGameplayStatics::OpenLevel(this, LocationName, false);
	TargetCharacter->SetActorLocation(GameInstance->GetPlayerLastLocationVector());
}
