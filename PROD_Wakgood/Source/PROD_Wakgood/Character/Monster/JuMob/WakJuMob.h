// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/Character/Monster/Monster_Base.h"
#include "WakJuMob.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakJuMob : public AMonster_Base
{
	GENERATED_BODY()

	
public:
	AWakJuMob();

	void CallAllJuMob();
};
