// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PROD_Wakgood/AI/WakAIC_Base.h"
#include "WakAIC_Wakmusae.generated.h"

/**
 * Navigation Mesh Agent Height를 아무리 설정해봐도 날아다니는 애들은 잘 안먹히는걸 보니....
 * 이동 관련 로직은 비헤이비어 트리 대신 일정 거리를 반복만 하게 AI Controller에 작성해야 할듯
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

	static const FName Wakmusae_HomePosKey;
	static const FName Wakmusae_PatrolPosKey;
	static const FName Wakmusae_TargetKey;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
