// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBacteriaDan.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AWakBacteriaDan::AWakBacteriaDan()
{
	PrimaryActorTick.bCanEverTick = false;

	SetIsDamaged(false);

	LaunchVelocityZ = 500.0f;
	LaunchVelocityX = 100.0f;
	LaunchDirection = 0;
}

void AWakBacteriaDan::BacteriaDan_LaunchCharacter()
{
	if (GetIsDamaged())
	{
		LaunchVelocityZ *= 1.2;
	}

	LaunchCharacter(FVector(LaunchVelocityX * LaunchDirection, 0.0f, LaunchVelocityZ), true, true);
	SetIsDamaged(false);
}

void AWakBacteriaDan::BeginPlay()
{
	Super::BeginPlay();

	BacteriaDan_LaunchCharacter();
}

void AWakBacteriaDan::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	BacteriaDan_LaunchCharacter();
}
