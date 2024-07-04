// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\AbilitySystem\Abilities\WAKNormalAttack.h"
#include "..\..\..\Public\AbilitySystem\WAKASC.h"
#include "..\..\..\Public\WAKTag.h"

UWAKNormalAttack::UWAKNormalAttack()
{
	AbilityTags.AddTag(FWAKGameplayTags::Get().InputTag_Q);
	AbilityTags.AddTag(FWAKGameplayTags::Get().Character_Form_Normal);
	ActivationRequiredTags.AddTag(FWAKGameplayTags::Get().Character_Form_Normal);
}

void UWAKNormalAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Red,TEXT("Activate Normal Attack"));
}

void UWAKNormalAttack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Red,TEXT("Input Pressed Normal Attack button"));
	// UWAKASC* ASC = Cast<UWAKASC>(ActorInfo->AbilitySystemComponent);
	// if(ASC)
	// {
	// 	
	// }
}
