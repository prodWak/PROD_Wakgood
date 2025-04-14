// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/WakCharacterAnimInstance.h"

#include "Character/WakCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWakCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AWakCharacterBase>(TryGetPawnOwner());
	if(OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}	
}

void UWakCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	Velocity = OwningCharacter->GetVelocity();
	Speed = OwningCharacter->GetVelocity().Size2D();
	AirSpeed = Velocity.Z;
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
	bIsFalling = OwningMovementComponent->IsFalling();
}
