// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/WakPlayerController.h"

// Unreal Header
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Wak Header
#include "Character/WakGood/WakWakGoodCharacter.h"
#include "Interaction/WakWorldPortal.h"

void AWakPlayerController::BeginPlay()
{
	Super::BeginPlay();

	WakCharacter = Cast<AWakWakGoodCharacter>(GetCharacter());

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(IMC_Default, 0);
	}
}

void AWakPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Default
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ThisClass::Jump);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ThisClass::StopJumping);
		EnhancedInputComponent->BindAction(IA_Pause, ETriggerEvent::Started, this ,&ThisClass::GamePause);
		EnhancedInputComponent->BindAction(IA_Interaction, ETriggerEvent::Started, this, &AWakPlayerController::OnInteract);

		// Ability
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AWakPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(Rotation.Pitch, 0, 0);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);

	// Mesh 회전
	MovementVector.X > 0 ?
		GetCharacter()->GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, 0.f))
	: GetCharacter()->GetMesh()->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
}

void AWakPlayerController::Jump(const FInputActionValue& Value)
{
	GetCharacter()->Jump();
}

void AWakPlayerController::StopJumping(const FInputActionValue& Value)
{
	GetCharacter()->StopJumping();
}

void AWakPlayerController::GamePause(const FInputActionValue& Value)
{
	
}

void AWakPlayerController::OnInteract()
{
	if(!InteractionTarget){ return ;}
	
	SwitchInteractInput();
		
	InteractionInterface = Cast<IInteractionInterface>(InteractionTarget);
	if (InteractionInterface)
	{
		InteractionInterface->Interaction(GetCharacter());
	}
}

void AWakPlayerController::SwitchInteractInput()
{
	bIsInteractInput = !bIsInteractInput;
}

void AWakPlayerController::SetInteractionTarget(AActor* TargetActor)
{
	if(!InteractionTarget)
	{
		InteractionTarget = Cast<AInteractionBase>(TargetActor);
		return;
	}

	if (InteractionTarget)
	{
		InteractionTarget = nullptr;
	}
}

bool AWakPlayerController::GetIsInteractInput() const
{
	return bIsInteractInput;
}
