// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Dakdulgi/Wakgood_Dakdulgi.h"

// Component
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

// Kismet & BlueprintFunc
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Player
#include "Character/Player/Wakgood_DebugPlayer.h"

// AIC
#include "AI/Dakdulgi/AIC_Dakdulgi.h"

AWakgood_Dakdulgi::AWakgood_Dakdulgi()
{
	
}

void AWakgood_Dakdulgi::Attack()
{
	// Attack Logic...

	// Called by BTTaskNode Attack
	OnAttackEnd.Broadcast();
}