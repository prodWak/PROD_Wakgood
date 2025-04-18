// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WakWeaponBase.h"

// Unreal Header
#include "Components/BoxComponent.h"

AWakWeaponBase::AWakWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMeshComponent"));
	SetRootComponent(WeaponMeshComponent);
	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	WeaponCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionComponent"));
	WeaponCollisionComponent->SetupAttachment(RootComponent);
	WeaponCollisionComponent->SetBoxExtent(FVector(20.f));
	WeaponCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
