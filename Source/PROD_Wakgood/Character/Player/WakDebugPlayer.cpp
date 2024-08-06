// Fill out your copyright notice in the Description page of Project Settings.


#include "WakDebugPlayer.h"

// Camera
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Movement
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

// Components
#include "Components/CapsuleComponent.h"

// Kismet
#include "Kismet/GameplayStatics.h"

// BacteriaDan Test
#include "PROD_Wakgood/Character/Monster/BacteriaDan/WakBacteriaDan.h"
#include "DrawDebugHelpers.h"

AWakDebugPlayer::AWakDebugPlayer()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	SpringArm->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->SetUsingAbsoluteRotation(true);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -68.5));

	GetCapsuleComponent()->SetCapsuleHalfHeight(66.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	// Fixed Y axis
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, 1.0f, 0.0f));
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// Adjusting Movement
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->GravityScale = 5.0f;
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->FallingLateralFriction = 50.0f;
	JumpMaxHoldTime = 0.4f;

	// Smooth Rotation
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	
	// Take Damage Test
	Health = 100.0f;
}

void AWakDebugPlayer::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Health : %f"), Health);

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController == nullptr)
	{
		PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	}

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem
		= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AWakDebugPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AWakDebugPlayer::Move);

		// Jump
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &AWakDebugPlayer::Jump);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AWakDebugPlayer::StopJumping);

		// BacteriaDan Test
		EnhancedInputComponent->BindAction(IA_MeleeAttack, ETriggerEvent::Started, this, &AWakDebugPlayer::MeleeAttack);
	}
}

void AWakDebugPlayer::Move(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();

	if (GetController() != nullptr)
	{
		if (Input.Y != 0.0f)
		{
			AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Pitch, 0.0f)).GetUnitAxis(EAxis::X), Input.Y);
			UpdateMeshRotation(float(Input.Y));
		}
	}
}

void AWakDebugPlayer::UpdateMeshRotation(float Direction)
{
	if (Direction != 0.0f)
	{
		const FRotator Spin(FRotator(0.0f, 180.0f, 0.0f));
		const FRotator NotSpin(FRotator(0.0f, 0.0f, 0.0f));

		if (Direction >= 0.0f)
		{
			GetController()->SetControlRotation(NotSpin);
		}
		else if (Direction <= 0.0f)
		{
			GetController()->SetControlRotation(Spin);
		}
	}
}

void AWakDebugPlayer::MeleeAttack()
{
	FHitResult HitResult;
	FCollisionQueryParams QueryParams(NAME_None, false, this);

	bool bResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 100.0f,
		ECollisionChannel::ECC_Pawn,
		QueryParams
	);

	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.0f, FColor::Red, false, 2.0f, 1);

	if (bResult)
	{
		if (AWakBacteriaDan* Target = Cast<AWakBacteriaDan>(HitResult.GetActor()))
		{
			GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString("Hit"));
			Target->SetIsDamaged(true);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, FString("No Hit Actor"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, FString("No Result"));
	}
}
