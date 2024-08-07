// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBacteriaDan.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AWakBacteriaDan::AWakBacteriaDan()
{
	PrimaryActorTick.bCanEverTick = true;

	GroundDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("GroundDetector"));
	GroundDetector->SetupAttachment(GetRootComponent());
	GroundDetector->SetRelativeLocation(FVector(0.0f, 0.0f, -80.0f));
	GroundDetector->SetBoxExtent(FVector(25.0f, 25.0f, 10.0f));
	GroundDetector->OnComponentBeginOverlap.AddDynamic(this, &AWakBacteriaDan::BeginOverlap);

	IsDamaged = false;

	LaunchVelocityZ = 500.0f;
	LaunchVelocityX = 100.0f;
	LaunchDirection = 0;
}

void AWakBacteriaDan::BeginPlay()
{
	Super::BeginPlay();

	LaunchCharacter(FVector(0.0f, 0.0f, LaunchVelocityZ), true, true);
}

void AWakBacteriaDan::BeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	if (!IsDamaged)
	{
		LaunchCharacter(FVector(LaunchVelocityX * LaunchDirection, 0.0f, LaunchVelocityZ), true, true);
	}
	else
	{
		LaunchCharacter(FVector(LaunchVelocityX * LaunchDirection, 0.0f, LaunchVelocityZ * 1.5f), true, true);
	}
}
