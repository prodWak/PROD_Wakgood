// Fill out your copyright notice in the Description page of Project Settings.


#include "WakDulgi.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Components/BoxComponent.h"

AWakDulgi::AWakDulgi()
{
	GroundDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("GroundDetector"));
	GroundDetector->SetupAttachment(GetRootComponent());
	GroundDetector->SetRelativeLocation(FVector(80.0f, 0.0f, -240.0f));
	GroundDetector->SetBoxExtent(FVector(50.0f, 100.0f, 300.0f));
	GroundDetector->OnComponentEndOverlap.AddDynamic(this, &AWakDulgi::GroundEndOverlap);

	GetCharacterMovement()->DefaultLandMovementMode = EMovementMode::MOVE_Flying;
	GetCharacterMovement()->MaxFlySpeed = 400.0f;
}

void AWakDulgi::WalkForward(float Delta)
{
	AddMovementInput(GetActorForwardVector(), Delta);
}

void AWakDulgi::GroundEndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Detect world static collision channel ( Custom Preset )
	TurnCharacter();
}