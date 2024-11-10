// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTestActor.generated.h"
class UWAKASC;
class UAbilitySystemComponent;
class UGameplayEffect;
class UWAKAttributeSet;
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
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, Category="Gameplay Effect")
	TSubclassOf<UGameplayEffect> GameplayEffect;
	UPROPERTY()
	FGameplayTag TestTypeTag;

	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	bool IsPlayerOverlap = false;
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TestSM;

	UPROPERTY(EditAnywhere)
	UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere)
	UWAKASC* ASC;
	UPROPERTY(EditAnywhere)
	UWAKAttributeSet* AttributeSet;
};
