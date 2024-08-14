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

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> IA_Run;

	// Take Attack Test
	UPROPERTY(VisibleAnywhere, Category = Health)
	float Health;

	void Move(const FInputActionValue& Value);
	void StartRunning();
	void StopRunning();
	void UpdateMeshRotation(float Direction);


	// BacteriaDan Test
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_MeleeAttack;

	void MeleeAttack();
public:
	AWakDebugPlayer();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Take Attack Test
	FORCEINLINE void SetDamage(float Amount) 
	{ 
		Health -= FMath::Max(Amount, 0);

		UE_LOG(LogTemp, Warning, TEXT("Health : %f"), Health);

		if (Health <= 0)
		{ 
			this->Destroy();
		}
	}

protected:
	virtual void BeginPlay() override;
};
