// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Dakdulgi/Wakgood_Dakdulgi.h"

// Component
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

// Kismet & BlueprintFunc
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Player
#include "Character/Player/Wakgood_DebugPlayer.h"

// AIC
#include "AI/Dakdulgi/AIC_Dakdulgi.h"

AWakgood_Dakdulgi::AWakgood_Dakdulgi()
{
	// Y 이동 제한
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, 1.0f, 0.0f));
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// 회전
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);

	/*PlayerDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerDetector"));
	PlayerDetector->SetupAttachment(GetRootComponent());
	PlayerDetector->SetBoxExtent(FVector(100.0f, 100.0f, 50.0f));
	PlayerDetector->OnComponentBeginOverlap.AddDynamic(this, &AWakgood_Dakdulgi::BeginOverlap);
	PlayerDetector->OnComponentEndOverlap.AddDynamic(this, &AWakgood_Dakdulgi::EndOverlap);*/

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AWakgood_Dakdulgi::MoveToward(FVector WorldDirection, float Value)
{
	AddMovementInput(WorldDirection, Value);

	if (WorldDirection.Y < 0.000)
	{
		SetActorRotation(FRotator(0.0, 180.0, 0.0));
	}
	else if (WorldDirection.Y > 0.000)
	{
		SetActorRotation(FRotator(0.0, 0.0, 0.0));
	}
}

void AWakgood_Dakdulgi::BeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	if (AWakgood_DebugPlayer* Player = Cast<AWakgood_DebugPlayer>(OtherActor))
	{		
		AAIC_Dakdulgi* AIC_Dak = Cast<AAIC_Dakdulgi>(UAIBlueprintHelperLibrary::GetAIController(this));

		if (AIC_Dak != nullptr)
		{
			// AIC_Dak->SetTargetPawn(Player);
		}
	}
}

void AWakgood_Dakdulgi::EndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AWakgood_DebugPlayer* Player = Cast<AWakgood_DebugPlayer>(OtherActor))
	{
		AAIC_Dakdulgi* AIC_Dak = Cast<AAIC_Dakdulgi>(UAIBlueprintHelperLibrary::GetAIController(this));

		if (AIC_Dak != nullptr)
		{
			// AIC_Dak->InitTargetPawn();
		}
	}
}
