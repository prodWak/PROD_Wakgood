// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/WakPawnCombatComponent.h"

#include "Items/Weapons/WakWeaponBase.h"

void UWakPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
                                                    AWakWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(WakWeaponInfo.CurrentEquippedWeaponTag != InWeaponTagToRegister, TEXT("A [%s] has already been added as carried weapon."), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	WakWeaponInfo.CurrentEquippedWeaponTag = InWeaponTagToRegister;
	WakWeaponInfo.WakWeapon = InWeaponToRegister;

	if (bRegisterAsEquippedWeapon)
	{
		WakWeaponInfo.CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
}

void UWakPawnCombatComponent::SetWeaponInfo(FGameplayTag InWeaponTagToChange, AWakWeaponBase* InWeaponToChange)
{
	unimplemented();

	// TODO : 태그 변경, 무기 변경
}

AWakWeaponBase* UWakPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (WakWeaponInfo.CurrentEquippedWeaponTag == InWeaponTagToGet)
	{
		return WakWeaponInfo.WakWeapon;
	}
	
	return nullptr;
}

AWakWeaponBase* UWakPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!WakWeaponInfo.CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	
	return GetCharacterCarriedWeaponByTag(WakWeaponInfo.CurrentEquippedWeaponTag);
}
