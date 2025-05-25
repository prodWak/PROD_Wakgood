// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WakAnimInstanceBase.h"
#include "WakCharacterAnimInstance.generated.h"

class AWakCharacterBase;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakCharacterAnimInstance : public UWakAnimInstanceBase
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<AWakCharacterBase> OwningCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wak|LocomotionData")
	FVector Velocity = FVector::ZeroVector;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wak|LocomotionData")
	float Speed = 0.f;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wak|LocomotionData")
	float AirSpeed = 0.f;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wak|LocomotionData")
	bool bHasAcceleration = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wak|LocomotionData")
	bool bIsFalling = false;
};
