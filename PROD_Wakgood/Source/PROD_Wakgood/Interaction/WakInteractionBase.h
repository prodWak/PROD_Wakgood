// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WakInteractionInterface.h"
#include "WakInteractionBase.generated.h"


UCLASS()
class PROD_WAKGOOD_API AWakInteractionBase : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay();
public:	
	// Sets default values for this actor's properties
	AWakInteractionBase();

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	class USceneComponent* _RootComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* InteractionBox;
	
	UPROPERTY(EditAnywhere)
	class UPointLightComponent* PointLight;

	IInteractionInterface* Interface = nullptr;
	bool bIsOverlapped = false;

	UFUNCTION()
	virtual void Interaction(AActor* target) override;
};