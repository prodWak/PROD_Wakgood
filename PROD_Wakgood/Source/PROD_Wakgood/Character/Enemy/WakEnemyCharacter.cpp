// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/WakEnemyCharacter.h"

// Unreal Header
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"

// Wak Header
#include "Components/Combat/WakEnemyCombatComponent.h"
#include "DataAsset/StartUpData/WakStartUpDataBase.h"

AWakEnemyCharacter::AWakEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UWakEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
}

UWakPawnCombatComponent* AWakEnemyCharacter::GetWakPawnCombatComponent()
{
	return EnemyCombatComponent;
}

void AWakEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void AWakEnemyCharacter::InitEnemyStartUpData() const
{
	if (GetWakStartUpData().IsNull())
	{
		return;
	}

	// 런타임 스폰 시 에셋 로딩 처리
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		GetWakStartUpData().ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this]()->void
		{
			if (UWakStartUpDataBase* LoadedData = GetWakStartUpData().Get())
			{
				LoadedData->GiveToAbilitySystemComponent(GetWakAbilitySystemComponent());
			}
		})
	);
}
