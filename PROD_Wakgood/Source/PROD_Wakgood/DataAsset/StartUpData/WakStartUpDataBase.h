// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WakStartUpDataBase.generated.h"

class UWakAbilitySystemComponent;
class UWakGameplayAbility;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakStartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWakAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	// 게임이 시작되고 부여되는 어빌리티
	UPROPERTY(EditDefaultsOnly, Category = "Wak|StartUpData")
	TArray<TSubclassOf<UWakGameplayAbility>> ActivateOnGivenAbilities;

	// 특정 조건에서 발동되는 어빌리티 ( Hit, Death ... )
	UPROPERTY(EditDefaultsOnly, Category = "Wak|StartUpData")
	TArray<TSubclassOf<UWakGameplayAbility>> ReactiveAbilities;;

	void GrantAbilities(const TArray<TSubclassOf<UWakGameplayAbility>>& InAbilitiesToGive, UWakAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
