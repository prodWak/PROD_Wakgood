#include "WakPlayerCharacter.h"
#include "AbilitySystemComponent.h"

AWakPlayerCharacter::AWakPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWakPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
