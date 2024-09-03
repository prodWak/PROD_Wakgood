// Fill out your copyright notice in the Description page of Project Settings.


#include "WakLevelScript.h"

#include "WakMainGameInstance.h"
#include "PROD_Wakgood/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
AWakLevelScript::AWakLevelScript()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWakLevelScript::BeginPlay()
{
	Super::BeginPlay();
	UWakMainGameInstance* GameInstance = Cast<UWakMainGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance && GameInstance->GetPlayerLastLocationName() != TEXT("None"))
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			APawn* PlayerPawn = Cast<APawn>(PlayerController->GetPawn());
			if (PlayerPawn)
			{
				FVector LastLocationVector = GameInstance->GetPlayerLastLocationVector();
				PlayerPawn->SetActorLocation(LastLocationVector);
				UE_LOG(LogTemp, Warning, TEXT("SetActorLocation : %f, %f, %f"), LastLocationVector.X, LastLocationVector.Y, LastLocationVector.Z);
				GameInstance->SetPlayerLastLocation(0);
			}
		}
	}
}