// Fill out your copyright notice in the Description page of Project Settings.


#include "WakChimpanzee.h"

#include "Kismet/KismetSystemLibrary.h"

AWakChimpanzee::AWakChimpanzee()
{
	MaxAngryGauge = 100.0f;
	CurrentAngryGauge = 0.0f;
	AngryGaugeAmount = 10.0f;

	SetMode(EChimpanzeeMode::Normal);
}

/* Timer Cycle
* 
* Start Increase Timer					Start Decrease Timer	
* if CAG <= MAG							if CAG <= 0
*	  ClearTimer							ClearTimer
* 
*  -> Call Decrease Timer				-> Call Increase Timer
*/

void AWakChimpanzee::StartIncreaseAngryGaugeTimer()
{
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, FString("Start Timer"));

	// Increase Angry Gauge every 2 seconds
	GetWorldTimerManager().SetTimer(IncreaseAngryGaugeHandle, this,
		&AWakChimpanzee::IncreaseAngryGauge_Recursive, 2.0f, true, 2.0f);
}

void AWakChimpanzee::StartDecreaseAngryGaugeTImer()
{
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("Start Decrease Timer"));

	// Decrease Angry Gauge every 2 seconds
	GetWorldTimerManager().SetTimer(DecreaseAngryGaugeHandle, this,
		&AWakChimpanzee::DecreaseAngryGauge_Recursive, 1.0f, true, 1.0f);
}

void AWakChimpanzee::IncreaseAngryGauge_Recursive()
{
	CurrentAngryGauge += AngryGaugeAmount;
	UE_LOG(LogTemp, Warning, TEXT("AG : %f"), CurrentAngryGauge);

	if (MaxAngryGauge <= CurrentAngryGauge)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, FString("Clear Timer"));
		GetWorldTimerManager().ClearTimer(IncreaseAngryGaugeHandle);

		StartDecreaseAngryGaugeTImer();
	}
}

void AWakChimpanzee::DecreaseAngryGauge_Recursive()
{
	CurrentAngryGauge -= AngryGaugeAmount;
	UE_LOG(LogTemp, Warning, TEXT("AG : %f"), CurrentAngryGauge);

	if (CurrentAngryGauge <= 0)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("Clear Decrease Timer"));
		GetWorldTimerManager().ClearTimer(DecreaseAngryGaugeHandle);

		StartIncreaseAngryGaugeTimer();
	}
}

void AWakChimpanzee::SetMode(EChimpanzeeMode Type)
{
	Mode = Type;

	// TODO : Change Chimpanzee mesh or animation ...

	switch (Mode)
	{
	case EChimpanzeeMode::Normal:
	{
		break;
	}
	case EChimpanzeeMode::Angry:
	{
		break;
	}
	}
}
