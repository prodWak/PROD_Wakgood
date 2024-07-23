// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Monster/Monster_Base.h"
#include "WakWakmusae.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakWakmusae : public AMonster_Base
{
	GENERATED_BODY()

public:
	AWakWakmusae();

	void Attack();
	
};
