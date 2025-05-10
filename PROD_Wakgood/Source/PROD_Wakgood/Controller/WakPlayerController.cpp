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
#include "AbilitySystem/WakAbilitySystemComponent.h"

AWakPlayerController::AWakPlayerController()
{
	PlayerTeamId = FGenericTeamId(0);
}

void AWakPlayerController::BeginPlay()
{
	Super::BeginPlay();

	checkf(InputConfigDataAsset, TEXT("You forgot to assign a valid data asset as input config."));
	
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	}

	if (const AWakWakGoodCharacter* WakCharacter = Cast<AWakWakGoodCharacter>(GetCharacter()))
	{
		WakAbilitySystemComponent = WakCharacter->GetWakAbilitySystemComponent();
	}
	
	checkf(WakAbilitySystemComponent, TEXT("Failed to get %s by casting the character"), *GetNameSafe(WakAbilitySystemComponent));
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

		WakInputComponent->BindNativeInputAction(InputConfigDataAsset, WakGameplayTags::InputTag_Interaction,
			ETriggerEvent::Started, this, &ThisClass::OnInteract);

		WakInputComponent->BindNativeInputAction(InputConfigDataAsset, WakGameplayTags::InputTag_Pause,
			ETriggerEvent::Started, this, &ThisClass::GamePause);

		WakInputComponent->BindAbilityInputAction(InputConfigDataAsset, this,
			&ThisClass::AbilityInputPressed, &AWakPlayerController::AbilityInputReleased);
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

	// TODO : 메시 회전이 너무 부자연스러움, 부드럽게 회전 하는게 있었는데 뭐였더라
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
	// 이거 찾아서 해제
	unimplemented();
}

void AWakPlayerController::AbilityInputPressed(FGameplayTag InInputTag)
{
	WakAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AWakPlayerController::AbilityInputReleased(FGameplayTag InInputTag)
{
	WakAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

const FInputActionInstance* AWakPlayerController::GetInputActionInstance(const UInputAction* InInputAction) const
{
	const UEnhancedInputLocalPlayerSubsystem* EnhancedInput =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (EnhancedInput == nullptr)
	{
		return nullptr;
	}

	const UEnhancedPlayerInput* WakPlayerInput = EnhancedInput->GetPlayerInput();
	if (WakPlayerInput == nullptr)
	{
		return nullptr;
	}

	return WakPlayerInput->FindActionInstanceData(InInputAction);
}

float AWakPlayerController::GetElapsedSeconds(const UInputAction* InInputAction) const
{
	const FInputActionInstance* ActionData = GetInputActionInstance(InInputAction);
	if (ActionData == nullptr)
	{
		return 0.0f;
	}

	if (GEngine)
	{
		const FString Time = FString::Printf(TEXT("ElapsedSeconds : %f"), ActionData->GetElapsedTime());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *Time);
	}
	return ActionData->GetElapsedTime();
}

bool AWakPlayerController::IsAbsorptionAction(const UInputAction* InInputAction, const float AbsorbHoldTime) const
{
	return GetElapsedSeconds(InInputAction) > AbsorbHoldTime;
}

FGenericTeamId AWakPlayerController::GetGenericTeamId() const
{
	return PlayerTeamId;
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
