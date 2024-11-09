// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PlatformActor.generated.h"

class AWakPlayerCharacter;

UCLASS()
class PROD_WAKGOOD_API APlatformActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlatformActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlatformMesh;
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* UnderPlayerDetectBox;
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* UpperPlayerDetectBox;

	TObjectPtr<AWakPlayerCharacter> PlayerCharacter;

	UFUNCTION()
	void BeginOverlapUnder(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlapUnder(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void BeginOverlapUpper(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlapUpper(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
