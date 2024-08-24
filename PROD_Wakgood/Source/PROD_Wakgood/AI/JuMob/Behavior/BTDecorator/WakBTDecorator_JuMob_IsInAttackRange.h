// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "WakBTDecorator_JuMob_IsInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakBTDecorator_JuMob_IsInAttackRange : public UBTDecorator
{
	GENERATED_BODY()

	float AttackRadius;

public:
	UWakBTDecorator_JuMob_IsInAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
