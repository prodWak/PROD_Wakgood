// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WakGood/WakWakGoodCharacter.h"

// Unreal Header
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

// Wak Header
#include "Controller/WakPlayerController.h"

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

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
}

void AWakWakGoodCharacter::BeginPlay()
{
	Super::BeginPlay();

	WakPlayerController = GetController<AWakPlayerController>();
}

void AWakWakGoodCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (WakPlayerController == nullptr)
		{
			return;
		}
		
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Character : OnBeginOverlap Called")));		
		WakPlayerController->SetInteractionTarget(OtherActor);
	}
}

void AWakWakGoodCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (WakPlayerController == nullptr)
	{
		return;
	}
	
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Character : OnEndOverlap Called")));
	WakPlayerController->SetInteractionTarget(nullptr);
}
