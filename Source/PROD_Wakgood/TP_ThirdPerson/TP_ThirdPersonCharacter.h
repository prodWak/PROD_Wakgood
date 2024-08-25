// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PROD_Wakgood/Interaction/WakInteractionInterface.h"
#include "PROD_Wakgood/Interaction/WakInteractionBase.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "TP_ThirdPersonCharacter.generated.h"

class AWakItemBase;
class AInteractionBase;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UBoxComponent;
class AInteractionBase;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ATP_ThirdPersonCharacter : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	// interaction action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionAction;

	// �ӽ� interaction get action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GetAction;

	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionBox;

	// �κ��丮 & ������ ����
	UPROPERTY(VisibleInstanceOnly, Category = "Inventroy")
	AInteractionBase* OverlapItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	AInteractionBase* CurrentItem;

	// UI ���� ���� �߰�
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UUserWidget> ItemThumbnailWidgetClass;

	UPROPERTY()
	UUserWidget* ItemThumbnailWidget;

	UPROPERTY()
	UImage* ItemThumbnailImage;

private:
	IInteractionInterface* Interface = nullptr;

	// ������ ����
	bool bIsHoldingPickup;
	float PickupHoldTimeThreshold;
	FTimerHandle PickupHoldTimerHandle;

public:
	ATP_ThirdPersonCharacter();
	

protected:
	void Move(const FInputActionValue& Value);
	
	// interaction
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	AInteractionBase* InteractionTarget;
	
	void OnInteract();
	bool bIsInteractInput = false;

public:
	void switchInteractInput();
	bool getIsInteractInput();

	// ������ Pickup �Լ� ����
	void AddItemToInventory(AWakItemBase* Item);
	void PickupItem();

	// ������ ȹ�� �� Ű ���ε�
	void StartPickupHold();
	void StopPickupHold();
	void HandlePickupTimeout();

	// ������ ������� ������Ʈ�ϴ� �Լ� ����
	void UpdateItemThumbnail(UTexture2D* NewThumbnail);

	// ����� ������ �� �����ϴ��� Ȯ��
	void InitializeItemThumbnailWidget();
	
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	
	virtual void BeginPlay();

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// �浹���� item�� ������ �� �ִ� set �Լ� ����
	FORCEINLINE void SetOverlapItem(AInteractionBase* _overlapItem) { OverlapItem = _overlapItem; }
};