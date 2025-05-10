// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WakPlayerGameplayAbility.h"

#include "AbilitySystem/WakAbilitySystemComponent.h"
#include "Character/WakGood/WakWakGoodCharacter.h"
#include "Controller/WakPlayerController.h"

AWakWakGoodCharacter* UWakPlayerGameplayAbility::GetWakPlayerCharacterFromActorInfo()
{
	if (!CachedWakPlayerCharacter.IsValid())
	{
		CachedWakPlayerCharacter = Cast<AWakWakGoodCharacter>(CurrentActorInfo->AvatarActor);
	}
	
	return CachedWakPlayerCharacter.IsValid() ? CachedWakPlayerCharacter.Get() : nullptr;
}

AWakPlayerController* UWakPlayerGameplayAbility::GetWakPlayerControllerFromActorInfo()
{
	if (!CachedWakPlayerController.IsValid())
	{
		CachedWakPlayerController = Cast<AWakPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedWakPlayerController.IsValid() ? CachedWakPlayerController.Get() : nullptr;
}

UWakPlayerCombatComponent* UWakPlayerGameplayAbility::GetWakPlayerCombatComponentFromActorInfo()
{
	return GetWakPlayerCharacterFromActorInfo()->GetWakPlayerCombatComponent();
}

FGameplayEffectSpecHandle UWakPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle( TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage)
{
	check(EffectClass);

	const UWakAbilitySystemComponent* WakAbilitySystemComponent = GetWakAbilitySystemComponentFromActorInfo();
	check(WakAbilitySystemComponent);

	FGameplayEffectContextHandle ContextHandle = WakAbilitySystemComponent->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = WakAbilitySystemComponent->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
		);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(WakGameplayTags::SetByCaller_BaseDamage, InWeaponBaseDamage);

	return EffectSpecHandle;
}
