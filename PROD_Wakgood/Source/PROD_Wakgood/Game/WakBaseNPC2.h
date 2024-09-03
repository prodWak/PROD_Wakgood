// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "WakDialogueDataTable.h"
#include "PROD_Wakgood/Interaction/WakInteractionBase.h"
#include "WakBaseNPC2.generated.h"

class USphereComponent;
UCLASS()
class PROD_WAKGOOD_API AWakBaseNPC2 : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWakBaseNPC2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Interaction(AActor* target) override;

	/////// Create Trigger Sphere
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

	
	/////// BeginOverlap, EndOverlap 
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	////// Interaction
	UPROPERTY(EditAnywhere)
	bool IsInteracting = false;

	UFUNCTION()
	void EnterInteraction();

	UFUNCTION()
	void ExitInteraction();

	/////// Widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWakDialogueWidget> DialogueWidgetClass;

	UPROPERTY()
	class UWakDialogueWidget* TextWidget;

	/////// Dialogue
	UFUNCTION(BlueprintCallable)
	void StartDialogue();

	UFUNCTION(BlueprintCallable)
	void EndDialogue();


	////// DataTable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DialogueDataTable;

	UPROPERTY()
	FString NextDialogue;

	UPROPERTY()
	FString InstanceNPCName = "\0";

	UPROPERTY()
	uint8 idx = 0;

	UPROPERTY()
	TArray<FName> RowNum;

	UFUNCTION()
	FString NextText();

	
};
