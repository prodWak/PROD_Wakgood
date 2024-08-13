// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakLani.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackDelegate);

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakLani : public AMonster_Base
{
	GENERATED_BODY()

public:
	AWakLani();

	virtual void MeleeAttack(float Damage) override;
	FOnAttackDelegate OnAttackDelegate;
	
};
