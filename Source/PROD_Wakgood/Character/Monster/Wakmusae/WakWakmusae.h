// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakWakmusae.generated.h"

class AWakWakmusae_Projectile;
class AWakDebugPlayer;

DECLARE_MULTICAST_DELEGATE(FOnAttackDelegate);

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakWakmusae : public AMonster_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Collision)
	TObjectPtr<UBoxComponent> GroundDetector;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AWakWakmusae_Projectile> Wakmusae_ProjectileClass;

	TObjectPtr<AWakDebugPlayer> Target;

	UPROPERTY()
	bool IsDetectPlayer;

	UFUNCTION()
	void GroundEndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	AWakWakmusae();

	// Attack
	FOnAttackDelegate OnAttackDelegate;

	void Attack();
	void SpawnProjectile();

	// Movement
	void WalkToward(float Delta);

	// State
	FORCEINLINE bool GetIsDetectPlayer() const { return IsDetectPlayer; }
	FORCEINLINE void SetIsDetectPlayer(bool IsDetect) { IsDetectPlayer = IsDetect; }

protected:
	virtual void BeginPlay() override;
};
