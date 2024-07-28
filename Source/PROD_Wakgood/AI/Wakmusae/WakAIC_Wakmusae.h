// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_Wakmusae.generated.h"

/**
 *
 */

class AWakWakmusae;

UCLASS()
class PROD_WAKGOOD_API AWakAIC_Wakmusae : public AWakAIC_Base
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BT_Wakmusae;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBlackboardData> BB_Wakmusae;

	UPROPERTY()
	TObjectPtr<AWakWakmusae> OwningPawn;

	UPROPERTY()
	bool IsDetectPlayer;

public:
	AWakAIC_Wakmusae();

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE bool GetIsDetectPlayer() const { return IsDetectPlayer; }

	static const FName Wakmusae_TargetKey;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
