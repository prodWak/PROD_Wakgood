// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTestActor.generated.h"
class UGameplayEffect;
UCLASS()
class PROD_WAKGOOD_API AGameplayEffectTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameplayEffectTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> GameplayEffect;
	FGameplayTag TestTypeTag;

	
};
