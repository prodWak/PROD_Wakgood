// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Monster_Base.h"

AMonster_Base::AMonster_Base()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMonster_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonster_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}