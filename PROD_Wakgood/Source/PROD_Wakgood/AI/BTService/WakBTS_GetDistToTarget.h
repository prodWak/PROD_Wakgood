// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "WakBTS_GetDistToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakBTS_GetDistToTarget : public UBTService
{
	GENERATED_BODY()

	UWakBTS_GetDistToTarget();
	
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Wak|Target")
	FBlackboardKeySelector InTargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Wak|Target")
	FBlackboardKeySelector OutDistToTargetKey;
};
