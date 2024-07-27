// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WakWakmusae_Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class PROD_WAKGOOD_API AWakWakmusae_Projectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	TObjectPtr<UProjectileMovementComponent> Movement;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);
	
public:	
	AWakWakmusae_Projectile();

protected:
	virtual void BeginPlay() override;
};
