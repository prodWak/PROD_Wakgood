// Fill out your copyright notice in the Description page of Project Settings.


#include "WakDakdulgi.h"

// Component
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

// Kismet & BlueprintFunc
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Player
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

// AIC
#include "PROD_Wakgood/AI/Dakdulgi/WakAIC_Dakdulgi.h"

AWakDakdulgi::AWakDakdulgi()
{
	
}

void AWakDakdulgi::Attack()
{
	OnAttackDelegate.Broadcast();
}