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
	WeaponCollisionComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);

	SetInstigator(Cast<APawn>(GetOwner()));
}

void AWakWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const APawn* WeaponOwningPawn = GetInstigator<APawn>();
	checkf(WeaponOwningPawn, TEXT("You need to assign an instigator as the owning pawn for the weapon : %s"), *GetNameSafe(this));

	const APawn* HitPawn = Cast<APawn>(OtherActor);
	if (!HitPawn)
	{
		return;
	}

	if (WeaponOwningPawn != HitPawn)
	{
		OnWeaponHitTarget.ExecuteIfBound(OtherActor);
	}
}

void AWakWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const APawn* WeaponOwningPawn = GetInstigator<APawn>();
	checkf(WeaponOwningPawn, TEXT("You need to assign an instigator as the owning pawn for the weapon : %s"), *GetNameSafe(this));

	const APawn* HitPawn = Cast<APawn>(OtherActor);
	if (!HitPawn)
	{
		return;
	}

	if (WeaponOwningPawn != HitPawn)
	{
		OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
	}	
}
