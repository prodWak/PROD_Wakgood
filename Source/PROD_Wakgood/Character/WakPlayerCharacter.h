// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WAKTag.h"
#include "Character/WAKTestCharacter.h"
#include "WakPlayerCharacter.generated.h"
class UBoxComponent;
DECLARE_MULTICAST_DELEGATE(FOnMoveUnderPlatform);
/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakPlayerCharacter : public AWAKTestCharacter
{
	GENERATED_BODY()
	AWakPlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void BeginPlay() override;
	//추가 테스트용
	virtual void Die() override;
	UPROPERTY(EditAnywhere, Category= "Combat")
	float Lifespan = 5.f;
	
	virtual void Landed(const FHitResult& Hit) override;
public:
	UFUNCTION()
	void SetPlatformCollisionResponseBlock();
	UFUNCTION()
	void SetPlatformCollisionResponseIgnore();
	UFUNCTION()
	void MoveUnderPlatform();
	bool bAbleDown = false;

	FOnMoveUnderPlatform OnMoveUnderPlatform;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> Shiled;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayAbility>> InitialAbilityList;

	
};
