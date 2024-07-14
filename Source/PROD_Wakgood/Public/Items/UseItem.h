// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/MyItem.h"
#include "UseItem.generated.h"

/**
 *
 */
	UCLASS()
	class PROD_WAKGOOD_API AUseItem : public AMyItem
{
	GENERATED_BODY()

private:

protected:
	virtual void BeginPlay() override;
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public:
	void Pickup(class AMyCharacter* Character);

	AUseItem();
	~AUseItem();

	// ItemTexture 멤버 변수 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D* ItemTexture;
};
