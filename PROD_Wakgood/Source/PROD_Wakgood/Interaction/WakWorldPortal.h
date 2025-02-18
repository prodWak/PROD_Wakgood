// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WakInteractionBase.h"
#include "WakWorldPortal.generated.h"

UCLASS()
class PROD_WAKGOOD_API AWorldPortal : public AInteractionBase
{
	GENERATED_BODY()

	AWorldPortal();
	
	virtual void Interaction(AActor* target) override;

	virtual void BeginPlay() override;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	UPROPERTY(EditAnywhere, Category="Game Instance")
	int32 PlayerLastLocationIndex;

	UPROPERTY(EditAnywhere, Category="Game Instance")
	FName LocationName;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* WidgetComponent;

};