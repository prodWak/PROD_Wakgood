// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Monster/Monster_Base.h"
#include "Wakgood_Dakdulgi.generated.h"

class UBoxComponent;;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakgood_Dakdulgi : public AMonster_Base
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> PlayerDetector;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	AWakgood_Dakdulgi();

	void MoveToward(FVector WorldDirection, float Value = 1.0f);	
};
