// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem\WAKASC.h"
#include "WAKTag.h"
#include "Abilities/WakGA_AttackBase.h"
#include "Character\WAKTestCharacter.h"

void UWAKASC::AddCharacterAbilities(TMap<TSubclassOf<UGameplayAbility>,FGameplayTag>& StartupAbilities)
{
	for(TTuple<TSubclassOf<UGameplayAbility>, FGameplayTag>& Ability : StartupAbilities) //어빌리티는 StartupTag라는 변수를 보유하고 있어야함. 필수.
	{
		FGameplayAbilitySpec AbilitySpec(Ability.Key,1);
		AbilitySpec.SourceObject = this;
		if(Ability.Value.IsValid())
		{
			AbilitySpec.DynamicAbilityTags.AddTag(Ability.Value); //
		}
		GiveAbility(AbilitySpec);
	}
}

void UWAKASC::SetNormalMode()
{
	FGameplayAbilitySpec AbilitySpec(NormalAbility,1);
	UE_LOG(LogTemp,Warning,TEXT("Normal Mode Ability Spec Tag : %s"),*AbilitySpec.Ability.GetName());
	GiveAbilityToCharacter(AbilitySpec,FWAKGameplayTags::Get().Character_Form_Normal);
}



void UWAKASC::GiveAbilityToCharacter(FGameplayAbilitySpec AbilitySpec,FGameplayTag FormTag)
{
	if(!HasMatchingGameplayTag(FormTag))
	{
		RemoveLooseGameplayTag(CurrentFormTag);
		AddLooseGameplayTag(FormTag);
		CurrentFormTag = FormTag;
		ClearAllAbilities();
		CancelAllAbilities();
	}
	GiveAbilityAndActivateOnce(AbilitySpec);

	if(AbilitySpec.IsActive()) 
	{
		UE_LOG(LogTemp,Warning,TEXT("Active Success"));
		
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Active Failed"));
	}
	
	OnFormChange.Broadcast(FormTag); // 아이템화 시킬 경우 이 함수들을 다른곳으로 옮길것이기 때문에 Broadcast 방식을 채택
	
}

void UWAKASC::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	TArray<FGameplayAbilitySpec> ActivatableAbilitySpecs = GetActivatableAbilities();

	if(!InputTag.IsValid())
		return;
	
	for(FGameplayAbilitySpec Spec : ActivatableAbilitySpecs)
	{
		if(Spec.DynamicAbilityTags.HasTagExact(InputTag)) // activate가능한 어빌리티 중에서 Tag가 일치하는걸 찾아서
		{
			if(!Spec.IsActive()) //아직 액티브 되지 않았다면 액티브 시키고
			{
				TryActivateAbility(Spec.Handle);
			}
			else // 액티브 중이라면 InputPress 함수 발동시킴.
			{
				AbilitySpecInputPressed(Spec);
			}
		}
	}
}

void UWAKASC::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	TArray<FGameplayAbilitySpec> ActivatableAbilitySpecs = GetActivatableAbilities();

	if(!InputTag.IsValid())
		return;
	
	for(FGameplayAbilitySpec Spec : ActivatableAbilitySpecs)
	{
		if(Spec.DynamicAbilityTags.HasTagExact(InputTag)) // activate가능한 어빌리티 중에서 Tag가 일치하는걸 찾아서
		{
			if(!Spec.IsActive()) //아직 액티브 되지 않았다면 액티브 시키고
			{
				TryActivateAbility(Spec.Handle);
			}
			else // 액티브 중이라면 InputPress 함수 발동시킴.
			{
				AbilitySpecInputReleased(Spec);
			}
		}
	}
}

void UWAKASC::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);
	Spec.Ability->InputPressed(Spec.Handle,AbilityActorInfo.Get(),Spec.ActivationInfo);
}


void UWAKASC::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputReleased(Spec);
	Spec.Ability->InputReleased(Spec.Handle,AbilityActorInfo.Get(),Spec.ActivationInfo);
}