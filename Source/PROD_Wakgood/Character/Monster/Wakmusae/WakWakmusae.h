// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakWakmusae.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakWakmusae : public AMonster_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Collision)
	TObjectPtr<UBoxComponent> Detector;

	UFUNCTION()
	void GroundEndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	AWakWakmusae();

	// Attack
	void Attack();

	// Debug
	void WalkToward(float Delta);
protected:
	void TurnCharacter();
};
