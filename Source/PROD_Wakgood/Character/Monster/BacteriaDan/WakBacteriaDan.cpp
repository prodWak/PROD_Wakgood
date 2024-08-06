// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBacteriaDan.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AWakBacteriaDan::AWakBacteriaDan()
{
	GroundDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("GroundDetector"));
	GroundDetector->SetupAttachment(GetRootComponent());
	GroundDetector->SetRelativeLocation(FVector(0.0f, 0.0f, -80.0f));
	GroundDetector->SetBoxExtent(FVector(25.0f, 25.0f, 10.0f));
	GroundDetector->OnComponentBeginOverlap.AddDynamic(this, &AWakBacteriaDan::BeginOverlap);

	LaunchVelocityZ = 500.0f;

	IsDamaged = false;
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
		LaunchCharacter(FVector(0.0f, 0.0f, LaunchVelocityZ), true, true);
	}
	else
	{
		LaunchCharacter(FVector(0.0f, 0.0f, LaunchVelocityZ * 1.5f), true, true);
	}
}