// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WakDebugPlayer.generated.h"

// Camera
class USpringArmComponent;
class UCameraComponent;

// EnhancedInput
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PROD_WAKGOOD_API AWakDebugPlayer : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> IA_Jump;

	void Move(const FInputActionValue& Value);
	void UpdateMeshRotation(float Direction);

public:
	AWakDebugPlayer();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

};
