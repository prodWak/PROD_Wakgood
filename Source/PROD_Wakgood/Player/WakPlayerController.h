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
	
	void Move(const FInputActionValue& InputActionValue);
	TObjectPtr<UWAKASC> GetASC();
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	UInputMappingContext* WakContext;
	UInputAction* MoveAction;

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
	
public:	
	UFUNCTION()
	void GetEnemyCharacterUnderCursor();

	UFUNCTION(	)
	FVector GetRotationUnderCursor();
};
