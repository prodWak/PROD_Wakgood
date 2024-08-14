// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakIfari.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackDelegate);

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakIfari : public AMonster_Base
{
	GENERATED_BODY()

public:
	AWakIfari();

	virtual void MeleeAttack(float Damage) override;
	FOnAttackDelegate OnAttackDelegate;
};
