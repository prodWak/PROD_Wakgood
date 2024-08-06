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

	UPROPERTY(VisibleAnywhere, Category = Collision)
	TObjectPtr<UBoxComponent> GroundDetector;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);

	float LaunchVelocityZ;

	bool IsDamaged;

public:
	AWakBacteriaDan();

	FORCEINLINE void SetIsDamaged(bool Damaged) { IsDamaged = Damaged; }

protected:
	virtual void BeginPlay() override;
};
