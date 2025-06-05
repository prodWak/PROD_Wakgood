// Fill out your copyright notice in the Description page of Project Settings.


#include "WakMainGameInstance.h"

void UMainGameInstance::SetPlayerLastLocation(int32 LocationIndex)
{
	// TODO : LastLocationVector 에디터에서 설정 가능하게 할 것
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