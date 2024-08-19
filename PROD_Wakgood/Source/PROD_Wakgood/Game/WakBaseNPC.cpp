// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBaseNPC.h"

// Sets default values
AWakBaseNPC::AWakBaseNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

// Called when the game starts or when spawned
void AWakBaseNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWakBaseNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWakBaseNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 상호작용 시작 함수 
void AWakBaseNPC::EnterInteraction()
{
	
	isInteracting = true;
}

// 상호작용 종료 함수
void AWakBaseNPC::ExitInteraction()
{
	
	isInteracting = false;
}

void AWakBaseNPC::Interaction(AActor* target)
{
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, FString::Printf(TEXT("Call Interaction")));
	if (isInteracting)
	{
		ExitInteraction();
	}
	else
	{
		EnterInteraction();
	}
}