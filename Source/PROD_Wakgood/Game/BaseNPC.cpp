// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPC.h"

// Sets default values
ABaseNPC::ABaseNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

}

// Called when the game starts or when spawned
void ABaseNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 상호작용 시작 함수 
void ABaseNPC::EnterInteraction()
{
	isInteracting = true;
}
// 상호작용 종료 함수
void ABaseNPC::ExitInteraction()
{
	isInteracting = false;
}
