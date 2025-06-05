// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WakPawnCombatInterface.generated.h"

class UWakPawnCombatComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWakPawnCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROD_WAKGOOD_API IWakPawnCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UWakPawnCombatComponent* GetWakPawnCombatComponent() = 0;
};
