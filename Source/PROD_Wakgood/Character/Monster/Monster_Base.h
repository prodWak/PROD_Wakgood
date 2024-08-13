// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster_Base.generated.h"

class UBoxComponent;

UCLASS()
class PROD_WAKGOOD_API AMonster_Base : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = State)
	bool IsDamaged;

public:
	AMonster_Base();

	virtual void WalkForward(float Delta);

	FORCEINLINE void SetIsDamaged(bool Damaged) { IsDamaged = Damaged; }
	FORCEINLINE bool GetIsDamaged() const { return IsDamaged; }

protected:
	virtual void TurnCharacter();
	virtual void MeleeAttack(float Damage);
};
