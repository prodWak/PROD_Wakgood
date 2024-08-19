// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PROD_Wakgood/Interaction/WakInteractionBase.h"
#include "WakBaseNPC.generated.h"

UCLASS()
class PROD_WAKGOOD_API AWakBaseNPC : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWakBaseNPC();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	AActor* BaseNPC = AWakBaseNPC::GetOwner();

	// 상호작용 시작
	UFUNCTION(BlueprintCallable)
	void EnterInteraction();

	// 상호작용 끝
	UFUNCTION(BlueprintCallable)
	void ExitInteraction();

	UFUNCTION(BlueprintCallable)
	virtual void Interaction(AActor* target) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//bool 변수 isinteracting 기본값 false
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "NPC")
	bool isInteracting = false;
};
