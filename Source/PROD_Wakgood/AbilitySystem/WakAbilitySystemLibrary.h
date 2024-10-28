// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WakAbilitySystemLibrary.generated.h"

class UAbilitySystemComponent;
class AWAKTestGameMode;
class CharacterClassInfo;
/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION()
	static void InitializeDefaultAttributes(const UObject* WorldContext, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

	UFUNCTION()
	static bool IsBlockHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION()
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION()
	static void SetIsBlockHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockHit);
	UFUNCTION()
	static void SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	
};
