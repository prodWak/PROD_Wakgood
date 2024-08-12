// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAmoeba.h"

#include "GameFramework/CharacterMovementComponent.h"

AWakAmoeba::AWakAmoeba()
{
	GetCharacterMovement()->MaxWalkSpeed = 50.0f;

	bCanTransformation = false;
}

void AWakAmoeba::CheckTransformation()
{
	if (bCanTransformation)
	{
		// Call Transformation Function in 5 second
		Transformation();
	}
}

void AWakAmoeba::Transformation()
{
	int32 Idx = FMath::RandRange(1, 7);
	TSubclassOf<AMonster_Base> SpawnMonsterClass = *MonsterList.Find(Idx);

	FVector Loc = GetActorLocation();
	FRotator Rot = GetActorRotation();
	FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// If the monster class is flying object, the Loc Z axis needs to be adjusted
	// idx : 2 (BatDan), 5 (Dulgi), 7 (Wakmusae)
	if (Idx == 2 || Idx == 5 || Idx == 7)
	{
		Loc.Z += 225;
	}

	this->Destroy();
	GetWorld()->SpawnActor<AMonster_Base>(SpawnMonsterClass, Loc, Rot, SpawnParams);
}