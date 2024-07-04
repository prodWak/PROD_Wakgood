// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\AbilitySystem\WAKASC.h"
#include "..\..\Public\WAKTag.h"
#include "..\..\Public\Character\WAKTestCharacter.h"

void UWAKASC::AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for(TSubclassOf<UGameplayAbility> Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(Ability,1);
		GiveAbility(AbilitySpec);
	}
}

void UWAKASC::SetNormalMode()
{
	FGameplayAbilitySpec AbilitySpec(NormalAbility,1);
	UE_LOG(LogTemp,Warning,TEXT("Normal Mode Ability Spec Tag : %s"),*AbilitySpec.Ability.GetName());
	GiveAbilityToCharacter(AbilitySpec,FWAKGameplayTags::Get().Character_Form_Normal);
}

void UWAKASC::SetMeleeMode()
{
	FGameplayAbilitySpec AbilitySpec(MeleeAbility,1);
	GiveAbilityToCharacter(AbilitySpec,FWAKGameplayTags::Get().Character_Form_Melee);
}

void UWAKASC::SetRangeMode()
{
	FGameplayAbilitySpec AbilitySpec(RangeAbility,1);
	GiveAbilityToCharacter(AbilitySpec,FWAKGameplayTags::Get().Character_Form_Range);
}

void UWAKASC::SetLongRangeMode()
{
	FGameplayAbilitySpec AbilitySpec(LongRangeAbility,1);
	GiveAbilityToCharacter(AbilitySpec,FWAKGameplayTags::Get().Character_Form_LongRange);
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
	ChangeAbility();

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



void UWAKASC::GiveAttackAbility(TArray<TSubclassOf<UGameplayAbility>> AttackAbility)
{
	int i = 0;
	for(TSubclassOf<UGameplayAbility> Ability : AttackAbility)
	{
		FGameplayAbilitySpec AbilitySpec(Ability,1);
		for(FGameplayTag Tag : AbilitySpec.Ability->AbilityTags)
		{
			AbilitySpec.DynamicAbilityTags.AddTag(Tag);
		}
		GiveAbility(AbilitySpec);
		i++;
	}
}

void UWAKASC::AbilityInputTagPressed(FGameplayTag InputTag)
{
	TArray<FGameplayAbilitySpec> ActivatableAbilitySpecs = GetActivatableAbilities();
	for(FGameplayAbilitySpec Spec : ActivatableAbilitySpecs)
	{
		if(!Spec.IsActive())
		{
			if(Spec.DynamicAbilityTags.HasTag(InputTag) )
			{
				TryActivateAbility(Spec.Handle);
			}
		}
		else
		{
			AbilitySpecInputPressed(Spec);
		}
		
	}
}

void UWAKASC::ChangeAbility()
{
	
	//Mesh 교체
	Cast<AWAKTestCharacter>(GetAvatarActor())->ChangeWeaponByTag();
	//Attack 어빌리티 활성화
	if(CurrentFormTag == FWAKGameplayTags::Get().Character_Form_Normal)
	{
		FGameplayAbilitySpec AbilitySpec(NormalAttackAbility1,1);
		AbilitySpec.DynamicAbilityTags.AddTag(FWAKGameplayTags::Get().InputTag_Q);
		GiveAbility(AbilitySpec);
	}
	else if(CurrentFormTag == FWAKGameplayTags::Get().Character_Form_Melee)
	{
		FGameplayAbilitySpec AbilitySpec(MeleeAttackAbility1,1);
		AbilitySpec.DynamicAbilityTags.AddTag(FWAKGameplayTags::Get().InputTag_Q);
		GiveAbility(AbilitySpec);
	}
	else if(CurrentFormTag == FWAKGameplayTags::Get().Character_Form_Range)
	{
		FGameplayAbilitySpec AbilitySpec(RangeAttackAbility1,1);
		AbilitySpec.DynamicAbilityTags.AddTag(FWAKGameplayTags::Get().InputTag_Q);
		GiveAbility(AbilitySpec);
	}
	else if(CurrentFormTag == FWAKGameplayTags::Get().Character_Form_LongRange)
	{
		FGameplayAbilitySpec AbilitySpec(LongRangeAttackAbility1,1);
		AbilitySpec.DynamicAbilityTags.AddTag(FWAKGameplayTags::Get().InputTag_Q);
		GiveAbility(AbilitySpec);
	}
}

void UWAKASC::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);
	Spec.Ability->InputPressed(Spec.Handle,AbilityActorInfo.Get(),Spec.ActivationInfo);
}


void UWAKASC::BindInputAction(UEnhancedInputComponent* InputComponent)
{
}

