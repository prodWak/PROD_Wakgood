// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WakGood/WakWakGoodCharacter.h"

// Unreal Header
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Wak Header
#include "DataAsset/StartUpData/WakStartUpDataBase.h"

AWakWakGoodCharacter::AWakWakGoodCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetWorldRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = 600.0f;
	
	FollowCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraComponent"));
	FollowCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FollowCameraComponent->bUsePawnControlRotation = false;
}

void AWakWakGoodCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWakWakGoodCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!GetWakStartUpData().IsNull())
	{
		UWakStartUpDataBase* LoadedData = GetWakStartUpData().LoadSynchronous();
		if (LoadedData)
		{
			LoadedData->GiveToAbilitySystemComponent(GetWakAbilitySystemComponent());
		}
	}
}
