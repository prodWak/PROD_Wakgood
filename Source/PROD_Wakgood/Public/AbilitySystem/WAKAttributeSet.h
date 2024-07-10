// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "WAKAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) 
UCLASS()
class PROD_WAKGOOD_API UWAKAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	UWAKAttributeSet();
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data);
	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue);

public:
	UPROPERTY(BlueprintReadOnly, Category="Primary Category")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UWAKAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category="Primary Category")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWAKAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category="Primary Category")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UWAKAttributeSet, Damage)

	UPROPERTY(BlueprintReadOnly, Category="Primary Category")
	FGameplayAttributeData Resist;
	ATTRIBUTE_ACCESSORS(UWAKAttributeSet, Resist)
	
	
};
