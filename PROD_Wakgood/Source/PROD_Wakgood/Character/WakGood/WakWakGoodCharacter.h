// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WakCharacterBase.h"
#include "WakWakGoodCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AWakPlayerController;

UCLASS()
class PROD_WAKGOOD_API AWakWakGoodCharacter : public AWakCharacterBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCameraComponent;

public:
	AWakWakGoodCharacter();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCameraComponent; }
};
