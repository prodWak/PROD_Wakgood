// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Monster/Monster_Base.h"
#include "Wakgood_Dakdulgi.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

class UBoxComponent;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakgood_Dakdulgi : public AMonster_Base
{
	GENERATED_BODY()

public:
	AWakgood_Dakdulgi();

	void MoveToward(FVector WorldDirection, float Value = 1.0f);

	void Attack();
	FOnAttackEndDelegate OnAttackEnd;
};
