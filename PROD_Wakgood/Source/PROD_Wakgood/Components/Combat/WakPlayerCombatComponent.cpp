// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/WakPlayerCombatComponent.h"

// Wak Header
#include "Items/Weapons/WakPlayerWeapon.h"

// Unreal Header
#include "AbilitySystemBlueprintLibrary.h"

AWakPlayerWeapon* UWakPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AWakPlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AWakPlayerWeapon* UWakPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
	return Cast<AWakPlayerWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UWakPlayerCombatComponent::GetPlayerCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UWakPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		WakGameplayTags::Event_Hit,
		EventData
		);
}

void UWakPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	
}
