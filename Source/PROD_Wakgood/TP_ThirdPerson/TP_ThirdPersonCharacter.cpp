// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_ThirdPersonCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Image.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PROD_Wakgood/Game/WakMainGameInstance.h"
#include "PROD_Wakgood/Interaction/WakWorldPortal.h"
#include "PROD_Wakgood/Interaction/WakItemBase.h"
#include "Blueprint/UserWidget.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATP_ThirdPersonCharacter



ATP_ThirdPersonCharacter::ATP_ThirdPersonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1000.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	// GetCharacterMovement()->MinAnalogWalkSpeed = 500.f;
	// GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	// GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetWorldRotation(FRotator(-30.f, 0.f, 0.f));
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 600.0f; // The camera follows at this distance behind the character	

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetCollisionProfileName(TEXT("OverlapAll"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)


	////////////////////////////////////////////////////////////
	// 인벤 & 아이템 관련
	CurrentItem = nullptr;
	bIsHoldingPickup = false;
	PickupHoldTimeThreshold = 2.0f;
}

void ATP_ThirdPersonCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ATP_ThirdPersonCharacter::OnBeginOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ATP_ThirdPersonCharacter::OnEndOverlap);
	UGameInstance* GameInstance = GetGameInstance();
	Cast<UMainGameInstance>(GameInstance);


	InitializeItemThumbnailWidget();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATP_ThirdPersonCharacter::switchInteractInput()
{
	if (bIsInteractInput)
	{
		bIsInteractInput = false;
	}
	else
	{
		bIsInteractInput = true;
	}
}

bool ATP_ThirdPersonCharacter::getIsInteractInput()
{
	return bIsInteractInput;
}



void ATP_ThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATP_ThirdPersonCharacter::Move);

		// interacting
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &ATP_ThirdPersonCharacter::OnInteract);

		// Get
		EnhancedInputComponent->BindAction(GetAction, ETriggerEvent::Started, this, &ATP_ThirdPersonCharacter::StartPickupHold);
		EnhancedInputComponent->BindAction(GetAction, ETriggerEvent::Completed, this, &ATP_ThirdPersonCharacter::StopPickupHold);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATP_ThirdPersonCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(Rotation.Pitch, 0, 0);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATP_ThirdPersonCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Character : OnBeginOverlap Called")));

	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if(!InteractionTarget && GetWorld())
		{
			InteractionTarget = Cast<AInteractionBase>(OtherActor);
		}
	}
}

void ATP_ThirdPersonCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Character : OnEndOverlap Called")));
	if (InteractionTarget)
	{
		InteractionTarget = nullptr;
	}
}

void ATP_ThirdPersonCharacter::OnInteract()
{
	if (Controller != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Interaction Input Detected")));
		switchInteractInput();
		if(InteractionTarget != nullptr)
		{
			Interface = Cast<IInteractionInterface>(InteractionTarget);
			if (Interface)
			{
				Interface->Interaction(this);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("null interactionTarget")));
		}
	}
}




////////////////////////////////////////////////////////////////
/* 아이템 관련 */

void ATP_ThirdPersonCharacter::AddItemToInventory(AWakItemBase* Item)
{
	if (CurrentItem)
	{
		CurrentItem->Destroy();
	}

	CurrentItem = Item;

	if (GEngine)
	{
		FString ItemName = Item->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Picked up: %s"), *ItemName));
	}

	// 아이템의 썸네일 업데이트
	if (Item->ItemTexture)
	{
		UpdateItemThumbnail(Item->ItemTexture);
		if (ItemThumbnailWidget)
		{
			UFunction* UpdateItemIconFunction = ItemThumbnailWidget->FindFunction(TEXT("UpdateItemIcon"));
			if (UpdateItemIconFunction)
			{
				struct FUpdateItemIconParams
				{
					UTexture2D* NewIcon;
				};

				FUpdateItemIconParams Params;
				Params.NewIcon = Item->ItemTexture;
				ItemThumbnailWidget->ProcessEvent(UpdateItemIconFunction, &Params);
			}
		}
	}
}

void ATP_ThirdPersonCharacter::PickupItem()
{
	if (OverlapItem)
	{
		AWakItemBase* NewItem = Cast<AWakItemBase>(OverlapItem);
		if (NewItem)
		{
			if (CurrentItem)
			{
				CurrentItem->Destroy();
			}

			NewItem->Interaction(this);
			CurrentItem = NewItem;
		}
	}
}

void ATP_ThirdPersonCharacter::StartPickupHold()
{
	if (CurrentItem)
	{
		bIsHoldingPickup = true;
		GetWorldTimerManager().SetTimer(PickupHoldTimerHandle, this, &ATP_ThirdPersonCharacter::HandlePickupTimeout, PickupHoldTimeThreshold, false);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Holding Pickup..."));
		}
	}
	else
	{
		PickupItem();
	}
}

void ATP_ThirdPersonCharacter::StopPickupHold()
{
	if (bIsHoldingPickup)
	{
		bIsHoldingPickup = false;
		GetWorldTimerManager().ClearTimer(PickupHoldTimerHandle);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Pickup Hold Stopped"));
		}
	}
}

void ATP_ThirdPersonCharacter::HandlePickupTimeout()
{
	if (OverlapItem)
	{
		AWakItemBase* UseItem = Cast<AWakItemBase>(OverlapItem);
		if (UseItem)
		{
			if (CurrentItem)
			{
				CurrentItem->Destroy();
			}
			UseItem->Interaction(this);

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Item Picked Up After Hold"));
			}
		}
	}
}

void ATP_ThirdPersonCharacter::UpdateItemThumbnail(UTexture2D* NewThumbnail)
{
	if (ItemThumbnailImage && NewThumbnail)
	{
		ItemThumbnailImage->SetBrushFromTexture(NewThumbnail);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Item Thumbnail Updated"));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to update Item Thumbnail"));
		}
	}
}

// 아이템 썸네일 위젯 초기화
void ATP_ThirdPersonCharacter::InitializeItemThumbnailWidget()
{
	if (ItemThumbnailWidgetClass)
	{
		ItemThumbnailWidget = CreateWidget<UUserWidget>(GetWorld(), ItemThumbnailWidgetClass);
		if (ItemThumbnailWidget)
		{
			ItemThumbnailWidget->AddToViewport();
			UImage* Image = Cast<UImage>(ItemThumbnailWidget->GetWidgetFromName(TEXT("Icon_Image")));
			if (Image)
			{
				ItemThumbnailImage = Image;
			}
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Icon_Image not found in ItemThumbnailWidget"));
				}
			}
		}
	}
}
/* 아이템 관련 끝 */