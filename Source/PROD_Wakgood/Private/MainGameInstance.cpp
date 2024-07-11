// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

void UMainGameInstance::SetPlayerLastLocation(int32 LocationIndex)
{
	switch (LocationIndex)
	{
		case 1:
			LastLocationName = "MAP_Debug";
			LastLocationVector = FVector(60, 800, 40);
			UE_LOG(LogTemp, Warning, TEXT("Last Location : MAP_Debug"));

			break;
		case 2:
			LastLocationName = "MAP_Debug";
			LastLocationVector = FVector(60, 1180, 40);
			UE_LOG(LogTemp, Warning, TEXT("Last Location : MAP_Debug"));

			break;
		default:
			LastLocationName = "None";
			LastLocationVector = FVector(0, 0, 40);
			UE_LOG(LogTemp, Warning, TEXT("Init Location Data"));
	}
}

FName UMainGameInstance::GetPlayerLastLocationName()
{
	return LastLocationName;
}

FVector UMainGameInstance::GetPlayerLastLocationVector()
{
	return LastLocationVector;
}
