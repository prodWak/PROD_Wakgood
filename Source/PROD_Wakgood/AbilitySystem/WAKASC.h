// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "InputAction.h"

#include "WAKASC.generated.h"
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFormChange, FGameplayTag)
/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWAKASC : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void AddCharacterAbilities(TMap<TSubclassOf<UGameplayAbility>,FGameplayTag>& StartupAbilities);

	UFUNCTION(CallInEditor)
	void SetNormalMode();
	UFUNCTION(CallInEditor)
	void GiveAbilityToCharacter(FGameplayAbilitySpec AbilitySpec, FGameplayTag FormTag);
	UFUNCTION()
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	UFUNCTION()
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	UPROPERTY()
	FGameplayTag CurrentFormTag;


	UFUNCTION()
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	UFUNCTION()
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;

	
	TArray<FGameplayAbilitySpec> AbilitySpecs;
	FOnFormChange OnFormChange; 

	UPROPERTY(EditDefaultsOnly,Category="Attack Ability")
	TSubclassOf<UGameplayAbility> NormalAttackAbility1;
	
	
private:
	UPROPERTY(EditDefaultsOnly,Category="Form Ability")
	TSubclassOf<UGameplayAbility> NormalAbility;


	UPROPERTY(EditDefaultsOnly, Category="Input Actions")
	UInputAction* IA_NormalAttack;

	
	
	
};



