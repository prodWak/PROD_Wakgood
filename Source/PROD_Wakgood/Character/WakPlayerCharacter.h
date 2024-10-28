// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WAKTag.h"
#include "Character/WAKTestCharacter.h"
#include "WakPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakPlayerCharacter : public AWAKTestCharacter
{
	GENERATED_BODY()
	AWakPlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;

	//추가 테스트용
	virtual void Die() override;
	UPROPERTY(EditAnywhere, Category= "Combat")
	float Lifespan = 5.f;
};
