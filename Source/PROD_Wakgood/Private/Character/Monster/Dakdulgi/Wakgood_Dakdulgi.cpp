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
	// Y 이동 제한
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, 1.0f, 0.0f));
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// 회전
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AWakgood_Dakdulgi::MoveToward(FVector WorldDirection, float Value)
{
	AddMovementInput(WorldDirection, Value);

	if (WorldDirection.Y < 0.000)
	{
		SetActorRotation(FRotator(0.0, 180.0, 0.0));
	}
	else if (WorldDirection.Y > 0.000)
	{
		SetActorRotation(FRotator(0.0, 0.0, 0.0));
	}
}

void AWakgood_Dakdulgi::Attack()
{
	// Attack Logic...

	// Called by BTTaskNode Attack
	OnAttackEnd.Broadcast();
}