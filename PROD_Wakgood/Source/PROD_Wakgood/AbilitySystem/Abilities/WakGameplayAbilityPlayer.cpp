// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WakGameplayAbilityPlayer.h"

#include "AbilitySystem/WakAbilitySystemComponent.h"
#include "Character/WakGood/WakWakGoodCharacter.h"
#include "Controller/WakPlayerController.h"

AWakWakGoodCharacter* UWakGameplayAbilityPlayer::GetWakPlayerCharacterFromActorInfo()
{
	if (!CachedWakPlayerCharacter.IsValid())
	{
		CachedWakPlayerCharacter = Cast<AWakWakGoodCharacter>(CurrentActorInfo->AvatarActor);
	}
	
	return CachedWakPlayerCharacter.IsValid() ? CachedWakPlayerCharacter.Get() : nullptr;
}

AWakPlayerController* UWakGameplayAbilityPlayer::GetWakPlayerControllerFromActorInfo()
{
	if (!CachedWakPlayerController.IsValid())
	{
		CachedWakPlayerController = Cast<AWakPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedWakPlayerController.IsValid() ? CachedWakPlayerController.Get() : nullptr;
}

UWakPlayerCombatComponent* UWakGameplayAbilityPlayer::GetWakPlayerCombatComponentFromActorInfo()
{
	return GetWakPlayerCharacterFromActorInfo()->GetWakPlayerCombatComponent();
}

FGameplayEffectSpecHandle UWakGameplayAbilityPlayer::MakePlayerDamageEffectSpecHandle( TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage)
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
