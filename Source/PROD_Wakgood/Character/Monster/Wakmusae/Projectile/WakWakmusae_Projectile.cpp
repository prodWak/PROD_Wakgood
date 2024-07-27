// Fill out your copyright notice in the Description page of Project Settings.


#include "WakWakmusae_Projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

AWakWakmusae_Projectile::AWakWakmusae_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	Sphere->InitSphereRadius(50.0f);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AWakWakmusae_Projectile::BeginOverlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 1000.0f;
	Movement->MaxSpeed = 1000.0f;
	Movement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 1.0f;
}

void AWakWakmusae_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWakWakmusae_Projectile::BeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	if (AWakDebugPlayer* Player = Cast<AWakDebugPlayer>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, FString("Overlap"));
		this->Destroy();
	}
}