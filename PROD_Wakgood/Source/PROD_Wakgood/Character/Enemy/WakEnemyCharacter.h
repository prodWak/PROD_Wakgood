// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WakCharacterBase.h"
#include "WakEnemyCharacter.generated.h"

class AWakAIController;
class UWakEnemyCombatComponent;
class UBehaviorTree;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakEnemyCharacter : public AWakCharacterBase
{
	GENERATED_BODY()
	
public:
	AWakEnemyCharacter();
	virtual UWakPawnCombatComponent* GetWakPawnCombatComponent() override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Combat")
	TObjectPtr<UWakEnemyCombatComponent> EnemyCombatComponent;

private:
	void InitEnemyStartUpData() const;

public:
	FORCEINLINE UWakEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
