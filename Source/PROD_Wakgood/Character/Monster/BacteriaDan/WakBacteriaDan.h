// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakBacteriaDan.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakBacteriaDan : public AMonster_Base
{
	GENERATED_BODY()

	float LaunchVelocityZ;
	float LaunchVelocityX;
	int32 LaunchDirection;

	FTimerHandle LaunchCharacterHandle;

	void BacteriaDan_LaunchCharacter();

public:
	AWakBacteriaDan();

	FORCEINLINE void SetLaunchDirection(int32 Direction) { LaunchDirection = Direction; }

protected:
	virtual void BeginPlay() override;
	virtual void Landed(const FHitResult& Hit) override;
};
