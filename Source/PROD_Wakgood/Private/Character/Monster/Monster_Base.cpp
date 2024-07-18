// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Monster_Base.h"

// Movement
#include "GameFramework/CharacterMovementComponent.h"

// Debug
#include "Character/Player/Wakgood_DebugPlayer.h"
#include "AI/AIC_Base.h"
#include "Components/BoxComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AMonster_Base::AMonster_Base()
{
	PrimaryActorTick.bCanEverTick = false;

	// Y 이동 제한
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, 1.0f, 0.0f));
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// 회전
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);

	PlayerDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerDetector"));
	PlayerDetector->SetupAttachment(GetRootComponent());
	PlayerDetector->SetBoxExtent(FVector(100.0f, 100.0f, 50.0f));
	PlayerDetector->OnComponentBeginOverlap.AddDynamic(this, &AMonster_Base::BeginOverlap);

	AIControllerClass = AAIC_Base::StaticClass();
}

void AMonster_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonster_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster_Base::BeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	if (AWakgood_DebugPlayer* Player = Cast<AWakgood_DebugPlayer>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Detect"));
	
		if (AAIC_Base* AIC = Cast<AAIC_Base>(UAIBlueprintHelperLibrary::GetAIController(this)))
		{
			AIC->SetTargetPawn(Player);
		}
	}
}
