// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WakFunctionLibrary.generated.h"

class UWakPawnCombatComponent;
class UWakAbilitySystemComponent;

struct FGameplayTag;

UENUM(BlueprintType)
enum class EWakConfirmType : uint8
{
	Yes,
	No
};

UENUM(BlueprintType)
enum class EWakValidType : uint8
{
	Valid,
	Invalid
};

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UWakAbilitySystemComponent* GetWakAbilitySystemComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Wak|Function Library")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Wak|Function Library")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);
	
	UFUNCTION(BlueprintCallable, Category = "Wak|Function Library", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWakConfirmType& OutConfirmType);

	static UWakPawnCombatComponent* GetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Wak|Function Library", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UWakPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EWakValidType& OutValidType);
};
