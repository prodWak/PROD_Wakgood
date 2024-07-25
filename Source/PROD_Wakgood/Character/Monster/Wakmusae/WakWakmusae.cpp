// Fill out your copyright notice in the Description page of Project Settings.


#include "WakWakmusae.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

AWakWakmusae::AWakWakmusae()
{
	PrimaryActorTick.bCanEverTick = false;

	Detector = CreateDefaultSubobject<UBoxComponent>(TEXT("Detector"));
	Detector->SetupAttachment(GetRootComponent());
	Detector->SetRelativeLocation(FVector(80.0f, 0.0f, -240.0f));
	Detector->SetBoxExtent(FVector(50.0f, 100.0f, 300.0f));
	Detector->OnComponentEndOverlap.AddDynamic(this, &AWakWakmusae::GroundEndOverlap);

	GetCharacterMovement()->DefaultLandMovementMode = EMovementMode::MOVE_Flying;
	GetCharacterMovement()->MaxFlySpeed = 400.0f;
}

void AWakWakmusae::Attack()
{
	// Attack Logic...
}

void AWakWakmusae::TurnCharacter()
{
	FRotator CombineA = GetActorRotation();
	FRotator CombineB = FRotator(0.0f, 180.0f, 0.0f);

	FRotator Result = UKismetMathLibrary::ComposeRotators(CombineA, CombineB);

	SetActorRotation(Result);
}

void AWakWakmusae::WalkToward(float Delta)
{
	AddMovementInput(GetActorForwardVector(), Delta);
}

void AWakWakmusae::GroundEndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Detects worldstatic collision channel ( Custom Preset )
	TurnCharacter();
}