// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "WakPlayerState.generated.h"
class UWAKAttributeSet;
class UWAKASC;
/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	AWakPlayerState();
public:
	UFUNCTION()
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	UFUNCTION()
	UWAKAttributeSet* GetAttributeSet(){return AttributeSet;}
private:
	UPROPERTY(VisibleAnywhere, Category="Ability")
	TObjectPtr<UWAKASC> ASC;
	UPROPERTY()
	TObjectPtr<UWAKAttributeSet> AttributeSet;
	
	
	
};
