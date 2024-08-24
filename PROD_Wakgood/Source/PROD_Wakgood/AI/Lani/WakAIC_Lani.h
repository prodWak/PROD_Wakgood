// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_Lani.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_Lani : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_Lani;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_Lani;
	const FName IsDamagedKey;

public:
	AWakAIC_Lani();
	const FName GetIsDamagedKey() const { return IsDamagedKey; }

protected:
	virtual void OnPossess(APawn* InPawn) override;

};
