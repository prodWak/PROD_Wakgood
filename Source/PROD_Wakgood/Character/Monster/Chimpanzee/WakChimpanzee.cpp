// Fill out your copyright notice in the Description page of Project Settings.


#include "WakChimpanzee.h"

#include "Kismet/KismetSystemLibrary.h"

AWakChimpanzee::AWakChimpanzee()
{
	MaxAngryGauge = 100.0f;
	CurrentAngryGauge = 0.0f;
}

void AWakChimpanzee::StartAngryGaugeTimer()
{
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, FString("Start Timer"));

	GetWorldTimerManager().SetTimer(IncreaseAngryGaugeHandle, this,
		&AWakChimpanzee::IncreaseAngryGauge_Recursive, 1.0f, true, 2.0f);
}

void AWakChimpanzee::IncreaseAngryGauge_Recursive()
{
	CurrentAngryGauge += 50.0f;

	if (MaxAngryGauge == CurrentAngryGauge)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, FString("Clear Timer"));
		GetWorldTimerManager().ClearTimer(IncreaseAngryGaugeHandle);
	}
}