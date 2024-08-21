// Fill out your copyright notice in the Description page of Project Settings.


#include "WakNeugeuja.h"

AWakNeugeuja::AWakNeugeuja()
{
	Key1 = 0;
	Key2 = 0;
	Interval = 0;
	bIsSpawnCompleted = false;
	bIsTeleporting = false;
}

void AWakNeugeuja::SpawnRandomMonster()
{
	SetInterval();

	switch (Interval)
	{
	case 1:
	{
		SpawnRandomMonster_One();
		break;
	}
	case 2:
	{
		SpawnRandomMonster_Two();
		break;
	}
	}
}

void AWakNeugeuja::SetKey()
{
	switch (Interval)
	{
	case 1:
	{
		Key1 = FMath::RandRange(1, 9);

		break;
	}
	case 2:
	{
		Key1 = FMath::RandRange(1, 9);
		Key2 = FMath::RandRange(1, 9);

		if (Key1 == Key2)
		{
			SetKey();
		}
		break;
	}
	}
}

void AWakNeugeuja::SetInterval()
{
	Interval = FMath::RandRange(1, 2);

	SetKey();
}

void AWakNeugeuja::SpawnRandomMonster_One()
{
	TSubclassOf<AMonster_Base> SpawnMonsterClass = *MonsterList.Find(Key1);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Loc = GetActorLocation();
	FRotator Rot = GetActorRotation();

	Loc.X -= 300;

	// spawn two monsters next to each other
	GetWorld()->SpawnActor<AMonster_Base>(SpawnMonsterClass, Loc, Rot, SpawnParams);

	bIsSpawnCompleted = true;
}

void AWakNeugeuja::SpawnRandomMonster_Two()
{
	TSubclassOf<AMonster_Base> SpawnMonsterClass_Left = *MonsterList.Find(Key1);
	TSubclassOf<AMonster_Base> SpawnMonsterClass_Right = *MonsterList.Find(Key2);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Loc_Left = GetActorLocation();
	FVector Loc_Right = GetActorLocation();

	Loc_Left.X -= 300;
	Loc_Right.X += 300;

	FRotator Rot = GetActorRotation();

	// spawn two monsters next to each other
	GetWorld()->SpawnActor<AMonster_Base>(SpawnMonsterClass_Left, Loc_Left, Rot, SpawnParams);
	GetWorld()->SpawnActor<AMonster_Base>(SpawnMonsterClass_Right, Loc_Right, Rot, SpawnParams);

	bIsSpawnCompleted = true;
}
