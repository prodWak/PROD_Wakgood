// Fill out your copyright notice in the Description page of Project Settings.


#include "WakWakmusae.h"

#include "GameFramework/CharacterMovementComponent.h"

AWakWakmusae::AWakWakmusae()
{
	GetCharacterMovement()->DefaultLandMovementMode = EMovementMode::MOVE_Flying;
	GetCharacterMovement()->MaxFlySpeed = 400.0f;
}

void AWakWakmusae::Attack()
{
	// Attack Logic...
}
