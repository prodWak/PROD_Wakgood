// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WAKTag.h"
#include "Character/WAKTestCharacter.h"
#include "WAKGA.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWAKGA : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	void ActivateAbilityAndChangeWeapon();

public:
    
};
