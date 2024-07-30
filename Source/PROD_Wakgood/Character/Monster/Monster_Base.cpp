// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Base.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"

AMonster_Base::AMonster_Base()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, 1.0f, 0.0f));
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMonster_Base::WalkForward(float Delta)
{
	AddMovementInput(GetActorForwardVector(), Delta);
}

void AMonster_Base::TurnCharacter()
{
	FRotator CombineA = GetActorRotation();
	FRotator CombineB = FRotator(0.0f, 180.0f, 0.0f);

	FRotator Result = UKismetMathLibrary::ComposeRotators(CombineA, CombineB);

	SetActorRotation(Result);
}
