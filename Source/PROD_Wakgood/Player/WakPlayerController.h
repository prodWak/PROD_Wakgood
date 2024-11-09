// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "Input/WAKInputConfig.h"
#include "WakPlayerController.generated.h"

class AWAKTestCharacter;
class UInputMappingContext;
class UInputAction;
class UWAKASC;
class USplineComponent;
/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	AWakPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void Jump();
	UFUNCTION()
	void PressedShift(bool InIsPressed);

	float BaseWalkSpeed = 650.f;

	float MaxWalkSpeed = 1000.f;
	 
	UPROPERTY()
	bool IsPressedShift = false;
	
	TObjectPtr<UWAKASC> GetASC();

	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);


	TObjectPtr<UWAKASC> WakAbilitySystem;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWAKInputConfig> InputConfig;

	FVector CachedDestination = FVector::ZeroVector; //목적지 위치.
	float FollowTime = 0.f; // 누르고 있는 시간.
	float ShortPressThreshhold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;
	
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	void AutoRun();

	UPROPERTY()
	TObjectPtr<AWAKTestCharacter> TargetActor;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere)
	UInputMappingContext* WakContext;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputA;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputD;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputS;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputW;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputESC;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputJ;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputK;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputM;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputLMB;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputRMB;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputSpace;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputShift;

	UFUNCTION()
	void SetPlayerCollisionIgnoreWhenOverPlatform();
	UFUNCTION()
	void SetPlayerCollisionBlock();

	
	float TimetoElaspse = 0.f;
	
	float GuardTimeThreshHold = 0.5f;

	UFUNCTION()
	void Guard(); // 내려가기인지 가드인지 체크

	UFUNCTION()
	void EndGuard();
public:	
	UFUNCTION()
	void GetEnemyCharacterUnderCursor();

	UFUNCTION(	)
	FVector GetRotationUnderCursor();
};
