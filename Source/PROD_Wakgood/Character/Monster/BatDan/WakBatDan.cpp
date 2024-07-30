// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBatDan.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

#include "Kismet/KismetMathLibrary.h"

#include "DrawDebugHelpers.h"

AWakBatDan::AWakBatDan()
	: Target(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	AttackDetector = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackDetector"));
	AttackDetector->SetupAttachment(GetRootComponent());
	AttackDetector->SetCapsuleHalfHeight(300.0f);
	AttackDetector->SetCapsuleRadius(50.0f);
	AttackDetector->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCharacterMovement()->DefaultLandMovementMode = EMovementMode::MOVE_Flying;
}

void AWakBatDan::Tick(float Delta)
{
	Super::Tick(Delta);

	if (AttackDetector->IsCollisionEnabled())
	{
		Custom_Debug_Log(Log, TEXT("Enabled"));
	}
	Custom_Debug_Log(Log, TEXT("Tick"));
}

void AWakBatDan::Attack()
{
	if (Target != nullptr)
	{
		AttackDetector->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		//FRotator LookAtTarget = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Target->GetActorLocation());
		// AttackDetector->SetRelativeRotation(LookAtTarget);
		// DrawDebugCapsule(GetWorld(), AttackDetector->GetComponentLocation(), 300.0f, 50.0f, LookAtTarget.Quaternion(), FColor::Green, false, 1.0f, 1);
		OnAttackDelegate.Broadcast();
	}
}

void AWakBatDan::BeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	if (AWakDebugPlayer* Player = Cast<AWakDebugPlayer>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(16, 1.0f, FColor::Red, FString("Attack"));
	}
}