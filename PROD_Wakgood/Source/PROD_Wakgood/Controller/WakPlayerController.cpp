// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/WakPlayerController.h"

// Unreal Header
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"

// Wak Header
#include "Character/WakGood/WakWakGoodCharacter.h"
#include "Components/Input/WakInputComponent.h"
#include "DataAsset/Input/WakInputConfig.h"
#include "Interaction/WakWorldPortal.h"
#include "WakGameplayTags.h"

void AWakPlayerController::BeginPlay()
{
	Super::BeginPlay();

	checkf(InputConfigDataAsset, TEXT("You forgot to assign a valid data asset as input config."));
	
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	}
}

void AWakPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	checkf(InputConfigDataAsset, TEXT("You forgot to assign a valid data asset as input config."));

	if (UWakInputComponent* WakInputComponent = CastChecked<UWakInputComponent>(InputComponent))
	{
		WakInputComponent->BindNativeInputAction(InputConfigDataAsset, WakGameplayTags::InputTag_Move,
			ETriggerEvent::Triggered, this, &ThisClass::Move);

		WakInputComponent->BindNativeInputAction(InputConfigDataAsset, WakGameplayTags::InputTag_Jump,
			ETriggerEvent::Started, this, &ThisClass::Jump);

		WakInputComponent->BindNativeInputAction(InputConfigDataAsset, WakGameplayTags::InputTag_Jump,
			ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AWakPlayerController::Move(const FInputActionValue& Value)
{
	ACharacter* WakCharacter = GetCharacter();
	if (WakCharacter == nullptr)
	{
		return;
	}

	USkeletalMeshComponent* CharacterMesh = WakCharacter->GetMesh();
	if (CharacterMesh == nullptr)
	{
		return;
	}
	
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(Rotation.Pitch, 0, 0);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	WakCharacter->AddMovementInput(RightDirection, MovementVector.X);
	
	/** Mesh 회전 */
	MovementVector.X > 0 ?
		CharacterMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f))
	: CharacterMesh->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
}

void AWakPlayerController::Jump(const FInputActionValue& Value)
{
	ACharacter* WakCharacter = GetCharacter();
	if (WakCharacter == nullptr)
	{
		return;
	}
	
	WakCharacter->Jump();
}

void AWakPlayerController::StopJumping(const FInputActionValue& Value)
{
	ACharacter* WakCharacter = GetCharacter();
	if (WakCharacter == nullptr)
	{
		return;
	}
	
	WakCharacter->StopJumping();
}

void AWakPlayerController::GamePause(const FInputActionValue& Value)
{
	unimplemented();
}

void AWakPlayerController::OnInteract()
{
	AWakWakGoodCharacter* WakCharacter = Cast<AWakWakGoodCharacter>(GetCharacter());
	if (WakCharacter == nullptr)
	{
		return;
	}
	
	if (const UCapsuleComponent* CapsuleComponent = WakCharacter->GetCapsuleComponent())
	{
		TArray<AActor*> OverlappingActors;		
		CapsuleComponent->GetOverlappingActors(OverlappingActors);
		
		for (AActor* OverlappingActor : OverlappingActors)
		{
			IInteractionInterface* InteractInterface = Cast<IInteractionInterface>(OverlappingActor);
			if(InteractInterface == nullptr)
			{
				continue;
			}
			
			SwitchInteractInput();
			InteractInterface->Interaction(WakCharacter);
			return;
		}
	}
}

void AWakPlayerController::SwitchInteractInput()
{
	bIsInteractInput = !bIsInteractInput;
}

bool AWakPlayerController::GetIsInteractInput() const
{
	return bIsInteractInput;
}
