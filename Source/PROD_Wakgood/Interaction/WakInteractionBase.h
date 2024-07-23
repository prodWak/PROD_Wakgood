// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "WakInteractionInterface.h"
#include "Components/PointLightComponent.h"
#include "WakInteractionBase.generated.h"


UCLASS()
class PROD_WAKGOOD_API AInteractionBase : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay();
public:	
	// Sets default values for this actor's properties
	AInteractionBase();

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	USceneComponent* _RootComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionBox;
	
	UPROPERTY(EditAnywhere)
	UPointLightComponent* PointLight;

	IInteractionInterface* Interface = nullptr;
	bool isOverlap = false;

	UFUNCTION()
	virtual void Interaction(AActor* target) override;
};