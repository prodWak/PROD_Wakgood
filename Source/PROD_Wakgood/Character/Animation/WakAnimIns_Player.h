// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WakAnimIns_Player.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakAnimIns_Player : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = true))
	float Speed;

public:
	UWakAnimIns_Player();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
