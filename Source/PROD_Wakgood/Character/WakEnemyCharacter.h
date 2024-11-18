// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WAKTag.h"
#include "Character/WAKTestCharacter.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "WakEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakEnemyCharacter : public AWAKTestCharacter
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag FormTag = FWAKGameplayTags::Get().Character_Form_Normal;

protected:
	int32 Level = 1;
	ECharacterClass CharacterClass = ECharacterClass::Fighter;
	virtual void InitializeAttributeToEffect() override;

private:
	virtual void HitReact(FGameplayTag Tag, int32 NewCount) override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> HitReactMontage;
	
	void Die() override;

};
