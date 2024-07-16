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
	void AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

public:
	UFUNCTION(CallInEditor)
	void SetNormalMode();
	UFUNCTION(CallInEditor)
	void SetMeleeMode();
	UFUNCTION(CallInEditor)
	void SetRangeMode();
	UFUNCTION(CallInEditor)
	void SetLongRangeMode();
	void GiveAbilityToCharacter(FGameplayAbilitySpec AbilitySpec, FGameplayTag FormTag);
	void BindInputAction(UEnhancedInputComponent* InputComponent);
	void GiveAttackAbility(TArray<TSubclassOf<UGameplayAbility>> AttackAbility);
	UFUNCTION()
	void AbilityInputTagPressed(FGameplayTag InputTag);
	UPROPERTY()
	FGameplayTag CurrentFormTag;

	UFUNCTION()
	void ChangeAbility();

	UFUNCTION()
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;

	
	TArray<FGameplayAbilitySpec> AbilitySpecs;
	FOnFormChange OnFormChange; 

	UPROPERTY(EditDefaultsOnly,Category="Attack Ability")
	TSubclassOf<UGameplayAbility> NormalAttackAbility1;
	UPROPERTY(EditDefaultsOnly,Category="Attack Ability")
	TSubclassOf<UGameplayAbility> MeleeAttackAbility1;
	UPROPERTY(EditDefaultsOnly,Category="Attack Ability")
	TSubclassOf<UGameplayAbility> RangeAttackAbility1;
	UPROPERTY(EditDefaultsOnly,Category="Attack Ability")
	TSubclassOf<UGameplayAbility> LongRangeAttackAbility1;
	
	
private:
	UPROPERTY(EditDefaultsOnly,Category="Form Ability")
	TSubclassOf<UGameplayAbility> NormalAbility;
	UPROPERTY(EditDefaultsOnly,Category="Form Ability")
	TSubclassOf<UGameplayAbility> MeleeAbility;
	UPROPERTY(EditDefaultsOnly,Category="Form Ability")
	TSubclassOf<UGameplayAbility> RangeAbility;
	UPROPERTY(EditDefaultsOnly,Category="Form Ability")
	TSubclassOf<UGameplayAbility> LongRangeAbility;


	UPROPERTY(EditDefaultsOnly, Category="Input Actions")
	UInputAction* IA_NormalAttack;
	UPROPERTY(EditDefaultsOnly, Category="Input Actions")
	UInputAction* IA_MeleeAttack;
	UPROPERTY(EditDefaultsOnly, Category="Input Actions")
	UInputAction* IA_RangeAttack;
	UPROPERTY(EditDefaultsOnly, Category="Input Actions")
	UInputAction* IA_LongRangeAttack;

	
	
	
};
