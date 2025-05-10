// Fill out your copyright notice in the Description page of Project Settings.


#include "Lib/WakFunctionLibrary.h"

#include "AbilitySystem/WakAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/Combat/WakPawnCombatComponent.h"
#include "WakGameplayTags.h"
#include "Interfaces/WakPawnCombatInterface.h"

UWakAbilitySystemComponent* UWakFunctionLibrary::GetWakAbilitySystemComponentFromActor(AActor* InActor)
{
	check(InActor);
	
	return CastChecked<UWakAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UWakFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UWakAbilitySystemComponent* ASC = GetWakAbilitySystemComponentFromActor(InActor);
	if (!ASC)
	{
		return;
	}
	
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UWakFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UWakAbilitySystemComponent* ASC = GetWakAbilitySystemComponentFromActor(InActor);
	if (!ASC)
	{
		return;
	}
	
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UWakFunctionLibrary::DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	const UWakAbilitySystemComponent* ASC = GetWakAbilitySystemComponentFromActor(InActor);
	if (!ASC)
	{
		return false;
	}
	
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UWakFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWakConfirmType& OutConfirmType)
{
	OutConfirmType = DoesActorHaveTag(InActor, TagToCheck) ? EWakConfirmType::Yes : EWakConfirmType::No;
}

UWakPawnCombatComponent* UWakFunctionLibrary::GetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);
	IWakPawnCombatInterface* PawnCombatInterface = Cast<IWakPawnCombatInterface>(InActor);
	if (PawnCombatInterface == nullptr)
	{
		return nullptr;
	}
	
	return PawnCombatInterface->GetWakPawnCombatComponent();
}

UWakPawnCombatComponent* UWakFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	EWakValidType& OutValidType)
{
	UWakPawnCombatComponent* CombatComponent = GetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EWakValidType::Valid : EWakValidType::Invalid;
	return CombatComponent;
}
