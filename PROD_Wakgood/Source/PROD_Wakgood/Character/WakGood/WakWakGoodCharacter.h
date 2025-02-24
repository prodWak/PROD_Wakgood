// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WakCharacterBase.h"
#include "WakWakGoodCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class AWakPlayerController;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakWakGoodCharacter : public AWakCharacterBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCameraComponent;
	
	/*
	 * Interaction
	 */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wak|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> InteractionBoxComponent;

	UPROPERTY()
	AWakPlayerController* WakPlayerController;

public:
	AWakWakGoodCharacter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Get
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCameraComponent; }
};
