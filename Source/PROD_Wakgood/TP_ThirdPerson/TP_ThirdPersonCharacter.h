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

	// 임시 interaction get action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GetAction;

	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionBox;

	// 인벤토리 & 아이템 관련
	UPROPERTY(VisibleInstanceOnly, Category = "Inventroy")
	AInteractionBase* OverlapItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	AInteractionBase* CurrentItem;

	// UI 관련 변수 추가
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UUserWidget> ItemThumbnailWidgetClass;

	UPROPERTY()
	UUserWidget* ItemThumbnailWidget;

	UPROPERTY()
	UImage* ItemThumbnailImage;

private:
	IInteractionInterface* Interface = nullptr;

	// 아이템 관련
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

	// 아이템 Pickup 함수 선언
	void AddItemToInventory(AWakItemBase* Item);
	void PickupItem();

	// 아이템 획득 시 키 바인딩
	void StartPickupHold();
	void StopPickupHold();
	void HandlePickupTimeout();

	// 아이템 썸네일을 업데이트하는 함수 선언
	void UpdateItemThumbnail(UTexture2D* NewThumbnail);

	// 썸네일 위젯이 잘 동작하는지 확인
	void InitializeItemThumbnailWidget();
	
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	
	virtual void BeginPlay();

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// 충돌중인 item을 저장할 수 있는 set 함수 선언
	FORCEINLINE void SetOverlapItem(AInteractionBase* _overlapItem) { OverlapItem = _overlapItem; }
};