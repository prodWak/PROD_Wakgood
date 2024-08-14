// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "WakBTService_Chimpanzee_Detect.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakBTService_Chimpanzee_Detect : public UBTService
{
	GENERATED_BODY()

public:
	UWakBTService_Chimpanzee_Detect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void DetectLogic(UBehaviorTreeComponent& OwnerComp);
};
