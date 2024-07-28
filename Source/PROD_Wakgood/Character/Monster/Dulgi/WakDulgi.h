// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakDulgi.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakDulgi : public AMonster_Base
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Collsion)
	TObjectPtr<UBoxComponent> GroundDetector;

	UFUNCTION()
	void GroundEndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	AWakDulgi();

	// Movement
	void WalkForward(float Delta);
};
