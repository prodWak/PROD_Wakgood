// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacter.generated.h"


class AMyItem;
class AUseItem;
class UInputMappingContext;
class UInputAction;


UCLASS()
class PROD_WAKGOOD_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 충돌중인 Item을 저장할 수 있는 Set 함수 선언
	FORCEINLINE void SetOverlapItem(AMyItem* _overlapItem) { OverlapItem = _overlapItem; }


	// 아이템 Pickup 함수 선언
	void AddItemToInventory(AUseItem* Item);
	void PickupItem();

	// 아이템 획득 시 키 바인딩
	void StartPickupHold();
	void StopPickupHold();
	void HandlePickupTimeout();

	// 아이템 썸네일을 업데이트하는 함수 선언
	void UpdateItemThumbnail(UTexture2D* NewThumbnail);


private:
	UPROPERTY(VisibleInstanceOnly, Category = "Inventroy")
	AMyItem* OverlapItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	AUseItem* CurrentItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input", meta = (AllowPrivateAccess = "true"))
	UInputAction* GetAction;

	bool bIsHoldingPickup;
	float PickupHoldTimeThreshold;

	FTimerHandle PickupHoldTimerHandle;

	// UI 관련 변수 추가
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UUserWidget> ItemThumbnailWidgetClass;

	UPROPERTY()
	UUserWidget* ItemThumbnailWidget;

	UPROPERTY()
	UImage* ItemThumbnailImage;

	// 썸네일 위젯이 잘 동작하는지 확인
	void InitializeItemThumbnailWidget();
};
