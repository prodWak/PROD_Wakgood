// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakJuMob.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackDelegate);

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakJuMob : public AMonster_Base
{
	GENERATED_BODY()

	
public:
	AWakJuMob();

	FOnAttackDelegate OnAttackDelegate;
	void CallAllJuMob();
	virtual void MeleeAttack(float Damage) override;;
};
