// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Wakgood_DebugPlayer.generated.h"

// Camera
class USpringArmComponent;
class UCameraComponent;

// EnhancedInput
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PROD_WAKGOOD_API AWakgood_DebugPlayer : public ACharacter
{
	GENERATED_BODY()

	///////////////
	//	VARIABLE //
	///////////////

#pragma region CAMERA
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera;

#pragma region MOVEMENT
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> IA_Jump;

	///////////////
	//	FUNCTION //
	///////////////

#pragma region MOVEMENT
	void Move(const FInputActionValue& Value);
	void UpdateMeshRotation(float Direction);

public:
	AWakgood_DebugPlayer();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

};
