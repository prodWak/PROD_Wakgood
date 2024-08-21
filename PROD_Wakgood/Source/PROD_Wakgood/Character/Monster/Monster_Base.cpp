// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Base.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include <PROD_Wakgood/Character/Player/WakDebugPlayer.h>

AMonster_Base::AMonster_Base()
{
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

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

void AMonster_Base::MeleeAttack(float Damage)
{
	FHitResult HitResult;
	FCollisionQueryParams QueryParams(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 80.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(50.0f)
	);

	if (bResult)
	{
		if (AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(HitResult.GetActor()))
		{
			GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, FString("Hit"));
			Target->SetDamage(Damage);
		}
	}
}
