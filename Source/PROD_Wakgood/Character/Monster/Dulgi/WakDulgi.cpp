// Fill out your copyright notice in the Description page of Project Settings.


#include "WakDulgi.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

#include "Kismet/KismetMathLibrary.h"

AWakDulgi::AWakDulgi()
	: Target(nullptr)
	, IsDetectPlayer(false)
{
	GroundDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("GroundDetector"));
	GroundDetector->SetupAttachment(GetRootComponent());
	GroundDetector->SetRelativeLocation(FVector(80.0f, 0.0f, -240.0f));
	GroundDetector->SetBoxExtent(FVector(50.0f, 100.0f, 300.0f));
	GroundDetector->OnComponentEndOverlap.AddDynamic(this, &AWakDulgi::GroundEndOverlap);

	GetCharacterMovement()->DefaultLandMovementMode = EMovementMode::MOVE_Flying;
	GetCharacterMovement()->MaxFlySpeed = 400.0f;

	KnockBackPowerHor = 1200.0f;
	KnockBackPowerVert = 800.0f;
}

void AWakDulgi::SetTarget(TObjectPtr<AWakDebugPlayer> TargetObject)
{
	Target = TargetObject;
}

void AWakDulgi::AttackTarget(APawn* TargetObject)
{
	AWakDebugPlayer* Player = Cast<AWakDebugPlayer>(TargetObject);

	FRotator LookatRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Player->GetActorLocation());
	float ForwardVecX = UKismetMathLibrary::GetForwardVector(LookatRotation).X;

	bool bPick = (ForwardVecX < 0) ? true : false;
	float LaunchValue = UKismetMathLibrary::SelectFloat(-1.0f, 1.0f, bPick);
	float LaunchVelocityX = LaunchValue * KnockBackPowerHor;
	float LaunchVelocityZ = -1.0f * KnockBackPowerVert;

	LaunchCharacter(FVector(LaunchVelocityX, 0.0f, LaunchVelocityZ), true, true);
}

void AWakDulgi::Attack()
{
	GEngine->AddOnScreenDebugMessage(16, 1.0f, FColor::Red, FString("Attack"));

	AttackTarget(Target);
}

void AWakDulgi::GroundEndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Detect world static collision channel ( Custom Preset )
	TurnCharacter();
}