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
	PrimaryActorTick.bCanEverTick = false;

	PlayerDetector = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerDetector"));
	PlayerDetector->SetupAttachment(GetRootComponent());
	PlayerDetector->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	PlayerDetector->SetCapsuleHalfHeight(400.0f);
	PlayerDetector->SetCapsuleRadius(50.0f);
	PlayerDetector->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlayerDetector->OnComponentBeginOverlap.AddDynamic(this, &AWakBatDan::BeginOverlap);

	GetCharacterMovement()->DefaultLandMovementMode = EMovementMode::MOVE_Flying;
}

void AWakBatDan::Attack()
{
	if (Target != nullptr)
	{
		SetPlayerDetectorRotation();
		OnAttackDelegate.Broadcast();
	}
}

void AWakBatDan::BeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	// Player Enters AttackRange
	if (AWakDebugPlayer* Player = Cast<AWakDebugPlayer>(OtherActor))
	{
		FVector Loc = GetActorLocation();
		FRotator Rot = PlayerDetector->GetComponentRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(ActorClass, Loc, Rot, SpawnParams);

		// TODO : Actor -> Player->SetDamage(50.0f);
	}
}

void AWakBatDan::SetPlayerDetectorRotation()
{
	PlayerDetector->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	FRotator LookAtTarget = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Target->GetActorLocation());
	LookAtTarget.Pitch += 90;
	PlayerDetector->SetWorldRotation(LookAtTarget);
}
