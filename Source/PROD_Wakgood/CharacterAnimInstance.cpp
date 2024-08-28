// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"
#include "MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MyCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	if (MyCharacter != nullptr)
	{
		MyCharacterMovement = MyCharacter->GetCharacterMovement();
	}
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (MyCharacterMovement != nullptr)
	{
		MoveLength = UKismetMathLibrary::VSizeXY(MyCharacterMovement->Velocity);
		isJump = MyCharacterMovement->IsFalling();
	}
}
