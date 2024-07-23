// Fill out your copyright notice in the Description page of Project Settings.


#include "Wakgood_Dakdulgi.h"

// Component
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

// Kismet & BlueprintFunc
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Player
#include "PROD_Wakgood/Character/Player/Wakgood_DebugPlayer.h"

// AIC
#include "PROD_Wakgood/AI/Dakdulgi/AIC_Dakdulgi.h"

AWakgood_Dakdulgi::AWakgood_Dakdulgi()
{
	
}

void AWakgood_Dakdulgi::Attack()
{
	// Attack Logic...

	// Called by BTTaskNode Attack
	OnAttackEnd.Broadcast();
}