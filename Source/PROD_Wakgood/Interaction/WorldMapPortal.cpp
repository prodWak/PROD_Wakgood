// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMapPortal.h"

#include "PROD_Wakgood/Game/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PROD_Wakgood/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

AWorldMapPortal::AWorldMapPortal()
{
	LocationName = TEXT("MAP_Debug");
}

void AWorldMapPortal::InteractionWithMe(AActor* target)
{
	Super::InteractionWithMe(target);
	UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetWorld()->GetGameInstance());
	ATP_ThirdPersonCharacter* targetCharacter = Cast<ATP_ThirdPersonCharacter>(target);
	if (GameInstance)
	{
		UGameplayStatics::OpenLevel(this, LocationName, false);
		targetCharacter->SetActorLocation(GameInstance->GetPlayerLastLocationVector());
	}
}
