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

	// �浹���� Item�� ������ �� �ִ� Set �Լ� ����
	FORCEINLINE void SetOverlapItem(AMyItem* _overlapItem) { OverlapItem = _overlapItem; }


	// ������ Pickup �Լ� ����
	void AddItemToInventory(AUseItem* Item);
	void PickupItem();

	// ������ ȹ�� �� Ű ���ε�
	void StartPickupHold();
	void StopPickupHold();
	void HandlePickupTimeout();

	// ������ ������� ������Ʈ�ϴ� �Լ� ����
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

	// UI ���� ���� �߰�
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UUserWidget> ItemThumbnailWidgetClass;

	UPROPERTY()
	UUserWidget* ItemThumbnailWidget;

	UPROPERTY()
	UImage* ItemThumbnailImage;

	// ����� ������ �� �����ϴ��� Ȯ��
	void InitializeItemThumbnailWidget();
};
