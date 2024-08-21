// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "WakBTDecorator_Dakdulbi_IsInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakBTDecorator_Dakdulbi_IsInAttackRange : public UBTDecorator
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Radius)
	float AttackRadius;
	
public:
	UWakBTDecorator_Dakdulbi_IsInAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
