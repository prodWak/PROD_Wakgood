// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "WakBTService_PoopDog_IsDamaged.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakBTService_PoopDog_IsDamaged : public UBTService
{
	GENERATED_BODY()

public:
	UWakBTService_PoopDog_IsDamaged();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void CheckIsDamaged(UBehaviorTreeComponent& OwnerComp);
	
};
