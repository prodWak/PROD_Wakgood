// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster_Base.generated.h"

class UBoxComponent;

UCLASS()
class PROD_WAKGOOD_API AMonster_Base : public ACharacter
{
	GENERATED_BODY()

	// 디버그용
	UPROPERTY(VisibleAnywhere, Category = Collision)
	TObjectPtr<UBoxComponent> PlayerDetector;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);

public:
	AMonster_Base();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

};
