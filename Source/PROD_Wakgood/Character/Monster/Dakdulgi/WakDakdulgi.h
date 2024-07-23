// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakDakdulgi.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakDakdulgi : public AMonster_Base
{
	GENERATED_BODY()

public:
	AWakDakdulgi();

	void Attack();
	FOnAttackEndDelegate OnAttackEnd;
};
