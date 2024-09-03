// Fill out your copyright notice in the Description page of Project Settings.


#include "WakWorldMapPortal.h"

#include "PROD_Wakgood/Game/WakMainGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PROD_Wakgood/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

AWakWorldMapPortal::AWakWorldMapPortal()
{
	LocationName = TEXT("MAP_Debug");
}

void AWakWorldMapPortal::Interaction(AActor* target)
{
	Super::Interaction(target);
	UWakMainGameInstance* GameInstance = Cast<UWakMainGameInstance>(GetWorld()->GetGameInstance());
	ATP_ThirdPersonCharacter* targetCharacter = Cast<ATP_ThirdPersonCharacter>(target);
	if (GameInstance)
	{
		UGameplayStatics::OpenLevel(this, LocationName, false);
		targetCharacter->SetActorLocation(GameInstance->GetPlayerLastLocationVector());
	}
}
