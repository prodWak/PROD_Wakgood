// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Monster_Base.h"

#include "GameFramework/CharacterMovementComponent.h"

AMonster_Base::AMonster_Base()
{
	PrimaryActorTick.bCanEverTick = false;

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