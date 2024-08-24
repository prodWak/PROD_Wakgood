// Fill out your copyright notice in the Description page of Project Settings.


#include "WakWakmusae.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Projectile/WakWakmusae_Projectile.h"

#include "Kismet/KismetMathLibrary.h"

#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

AWakWakmusae::AWakWakmusae()
{
	PrimaryActorTick.bCanEverTick = false;

	GroundDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("Detector"));
	GroundDetector->SetupAttachment(GetRootComponent());
	GroundDetector->SetRelativeLocation(FVector(80.0f, 0.0f, -240.0f));
	GroundDetector->SetBoxExtent(FVector(50.0f, 100.0f, 300.0f));
	GroundDetector->OnComponentEndOverlap.AddDynamic(this, &AWakWakmusae::GroundEndOverlap);

	GetCharacterMovement()->DefaultLandMovementMode = EMovementMode::MOVE_Flying;
	GetCharacterMovement()->MaxFlySpeed = 400.0f;
}

void AWakWakmusae::Attack()
{
	SpawnProjectile();
	OnAttackDelegate.Broadcast();
}

void AWakWakmusae::SpawnProjectile()
{
	if (Wakmusae_ProjectileClass != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector Loc = GetActorLocation();
		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());

		AWakWakmusae_Projectile* Projectile =
			GetWorld()->SpawnActor<AWakWakmusae_Projectile>(Wakmusae_ProjectileClass, Loc, Rot, SpawnParams);
	}
}

void AWakWakmusae::SetTarget(AWakDebugPlayer* target)
{
	Target = target;
}

void AWakWakmusae::GroundEndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Detects worldstatic collision channel ( Custom Preset )
	TurnCharacter();
}