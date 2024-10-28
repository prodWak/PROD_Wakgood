// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "WakProjectile.generated.h"

struct FGameplayEffectSpec;
class UBoxComponent;
class UProjectileMovementComponent;
UCLASS()
class PROD_WAKGOOD_API AWakProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWakProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UProjectileMovementComponent>  ProjectileMovementComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> CollisionBox;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FComponentBeginOverlapSignature BeginOverlapSignature;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	UProjectileMovementComponent* GetProjectileMovementComponent(){return ProjectileMovementComponent;}

	FGameplayEffectSpecHandle HitEffectSpecHandle;

	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	
};
