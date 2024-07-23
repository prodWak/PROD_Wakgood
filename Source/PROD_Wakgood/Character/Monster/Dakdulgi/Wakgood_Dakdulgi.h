// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "Wakgood_Dakdulgi.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakgood_Dakdulgi : public AMonster_Base
{
	GENERATED_BODY()

public:
	AWakgood_Dakdulgi();

	void Attack();
	FOnAttackEndDelegate OnAttackEnd;
};
