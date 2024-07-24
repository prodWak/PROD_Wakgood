// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseNPC.generated.h"

UCLASS()
class PROD_WAKGOOD_API ABaseNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseNPC();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 상호작용 시작
	UFUNCTION(BlueprintCallable)
	void EnterInteraction();

	// 상호작용 끝
	UFUNCTION(BlueprintCallable)
	void ExitInteraction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//bool 변수 isinteracting 기본값 false
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NPC")
	bool isInteracting = false;
};
