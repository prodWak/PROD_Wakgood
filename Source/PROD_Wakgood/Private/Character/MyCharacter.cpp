// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Items/MyItem.h"
#include "Items/UseItem.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentItem = nullptr;
    bIsHoldingPickup = false;
    PickupHoldTimeThreshold = 2.0f;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* EnhancedInputSystem;
		EnhancedInputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (EnhancedInputSystem != nullptr)
		{
			EnhancedInputSystem->AddMappingContext(MappingContext, 0);
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("MappingContext added"));
			}
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("EnhancedInputSystem is null"));
			}
		}
	}

    InitializeItemThumbnailWidget();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
        EnhancedInputComponent->BindAction(GetAction, ETriggerEvent::Started, this, &AMyCharacter::StartPickupHold);
        EnhancedInputComponent->BindAction(GetAction, ETriggerEvent::Completed, this, &AMyCharacter::StopPickupHold);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("InputComponent setup complete"));
		}
	}
}


void AMyCharacter::AddItemToInventory(AUseItem* Item)
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

void AMyCharacter::PickupItem()
{
    if (OverlapItem)
    {
        AUseItem* UseItem = Cast<AUseItem>(OverlapItem);
        if (UseItem)
        {
            if (CurrentItem)
            {
                CurrentItem->Destroy();
            }

            UseItem->Pickup(this);
            CurrentItem = UseItem;
        }
    }
}


// item먹은 후에 다른 아이템을 교체하기 위해 E 버튼을 눌렀을 경우
void AMyCharacter::StartPickupHold()
{
    if (CurrentItem)
    {
        bIsHoldingPickup = true;
        GetWorldTimerManager().SetTimer(PickupHoldTimerHandle, this, &AMyCharacter::HandlePickupTimeout, PickupHoldTimeThreshold, false);

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

// item에서 E 버튼 누르고 뗐을 경우
void AMyCharacter::StopPickupHold()
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

void AMyCharacter::HandlePickupTimeout()
{
    if (OverlapItem)
    {
        AUseItem* UseItem = Cast<AUseItem>(OverlapItem);
        if (UseItem)
        {
            if (CurrentItem)
            {
                CurrentItem->Destroy();
            }
            UseItem->Pickup(this);

            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Item Picked Up After Hold"));
            }
        }
    }
}

void AMyCharacter::UpdateItemThumbnail(UTexture2D* NewThumbnail)
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


// 이이템 썸네일 위젯 초기화
void AMyCharacter::InitializeItemThumbnailWidget()
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