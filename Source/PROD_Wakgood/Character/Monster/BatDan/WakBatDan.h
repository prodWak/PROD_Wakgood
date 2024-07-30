// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakBatDan.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackDelegate);

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakBatDan : public AMonster_Base
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Collision)
	TObjectPtr<UCapsuleComponent> AttackDetector;

	UPROPERTY()
	TObjectPtr<APawn> Target;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor
		, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);
	
public:
	AWakBatDan();

	virtual void Tick(float Delta) override;

	void Attack();
	FOnAttackDelegate OnAttackDelegate;

	FORCEINLINE void SetTarget(APawn* TargetObject) { Target = TargetObject; }
	FORCEINLINE TObjectPtr<UCapsuleComponent> GetAttackDetector() const { return AttackDetector; }

};
