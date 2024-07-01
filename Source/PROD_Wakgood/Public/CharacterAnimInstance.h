// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

class AMyCharacter;
class UCharacterMovementComponent;

UCLASS()
class PROD_WAKGOOD_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly)
	AMyCharacter* MyCharacter;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* MyCharacterMovement;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float MoveLength;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool isJump;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
};
