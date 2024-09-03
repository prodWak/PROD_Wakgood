// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WakInteractionBase.h"
#include "WakNPCBase.generated.h"

/**
 * 
 */

UCLASS()
class PROD_WAKGOOD_API AWakNPCBase : public AWakInteractionBase
{
	GENERATED_BODY()
	
public:
	AWakNPCBase();
	
protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void Interaction(AActor* target) override;
	
	/////// BeginOverlap, EndOverlap 
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	/////// Dialogue
	UFUNCTION(BlueprintCallable)
	void StartDialogue();

	UFUNCTION(BlueprintCallable)
	void EndDialogue();
	
	////// Interaction
	UPROPERTY(EditAnywhere)
	bool IsInteracting = false;

	UFUNCTION()
	void ExitInteraction();
	
	/////// Widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWakDialogueWidget> DialogueWidgetClass;

	UPROPERTY()
	class UWakDialogueWidget* TextWidget;
	
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


private:
	
	
};
