// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakDulgi.generated.h"

class AWakDebugPlayer;

DECLARE_MULTICAST_DELEGATE(FOnAttackDelegate);

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakDulgi : public AMonster_Base
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Collsion)
	TObjectPtr<UBoxComponent> GroundDetector;

	UPROPERTY()
	TObjectPtr<AWakDebugPlayer> Target;

	UPROPERTY()
	bool IsDetectPlayer;

	float KnockBackPowerHor;
	float KnockBackPowerVert;

	UFUNCTION()
	void PlayerBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Result);

	UFUNCTION()
	void GroundEndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	AWakDulgi();

	FORCEINLINE bool GetIsDetectPlayer()const { return IsDetectPlayer; }
	FORCEINLINE void SetIsDetectPlayer(bool IsDetect) { IsDetectPlayer = IsDetect; }

	void SetTarget(TObjectPtr<AWakDebugPlayer> TargetObject);
	void AttackTarget(APawn* TargetObject);

	void Attack();
	FOnAttackDelegate OnAttackDelegate;
};
