// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WakAIController.generated.h"

class UAISenseConfig_Sight;
class UAIPerceptionComponent;
struct FAIStimulus;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIController : public AAIController
{
	GENERATED_BODY()

public:
	AWakAIController();

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|AI")
	TObjectPtr<UAIPerceptionComponent> WakAIPerceptionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|AI")
	TObjectPtr<UAISenseConfig_Sight> WakAISenseConfig_Sight;
	
	/* UAISenseConfig_Hearing 추가 예정 */

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnPerceptionForgotten(AActor* Actor);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Wak|AI")
	TObjectPtr<UBehaviorTree> WakBehaviorTree;
};
