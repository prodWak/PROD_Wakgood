// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAnimIns_Player.h"

#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

UWakAnimIns_Player::UWakAnimIns_Player()
{
	Speed = 0.0f;
	IsInAir = false;
}

void UWakAnimIns_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (Pawn != nullptr)
	{
		Speed = Pawn->GetVelocity().Size();

		AWakDebugPlayer* Character = Cast<AWakDebugPlayer>(Pawn);
		if (Character != nullptr)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}
