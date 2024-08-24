// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_PoopDog.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_PoopDog : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_PoopDog;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_PoopDog;

	const FName PoopDog_IsDamagedKey;

public:
	AWakAIC_PoopDog();

	const FName GetIsDamagedKey() const { return PoopDog_IsDamagedKey; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
