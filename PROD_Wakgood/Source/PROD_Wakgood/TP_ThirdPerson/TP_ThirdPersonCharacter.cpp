// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_ThirdPersonCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PROD_Wakgood/Game/WakMainGameInstance.h"
#include "PROD_Wakgood/Interaction/WakWorldPortal.h"
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

		//Dialgoue
		EnhancedInputComponent->BindAction(DialogueAction, ETriggerEvent::Started, this, &ATP_ThirdPersonCharacter::Dialogue);
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

// Q키를 눌렀을 때 Binding된 대화 함수
void ATP_ThirdPersonCharacter::Dialogue()
{
	if (NPC != nullptr && NPC->IsInteracting == true)
	{
		NPC->StartDialogue();
	}
	else if (NPC == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, "None NPC");
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
		// overlap된 대상이 character형(npc) 이면 npc에 배정
		if (NPC == nullptr && OtherActor->IsA(ACharacter::StaticClass()))
		{
			NPC = Cast<AWakBaseNPC2>(OtherActor);
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

	// overlap이 끝나면 npc에 nullptr 배정
	NPC = nullptr;
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
