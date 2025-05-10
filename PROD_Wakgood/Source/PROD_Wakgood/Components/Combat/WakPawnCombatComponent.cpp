// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/WakPawnCombatComponent.h"

#include "Components/BoxComponent.h"
#include "Items/Weapons/WakWeaponBase.h"

void UWakPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
                                                    AWakWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(WakWeaponInfo.CurrentWeaponTag != InWeaponTagToRegister, TEXT("A [%s] has already been added as carried weapon."), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	WakWeaponInfo.CurrentWeaponTag = InWeaponTagToRegister;
	WakWeaponInfo.WakWeapon = InWeaponToRegister;

	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	// 검색용 태그 할당
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
}

void UWakPawnCombatComponent::SetWeaponInfo(FGameplayTag InWeaponTagToChange, AWakWeaponBase* InWeaponToChange)
{
	unimplemented();

	// TODO : 태그 변경, 무기 변경
}

AWakWeaponBase* UWakPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (WakWeaponInfo.CurrentWeaponTag == InWeaponTagToGet)
	{
		return WakWeaponInfo.WakWeapon;
	}
	
	return nullptr;
}

AWakWeaponBase* UWakPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!WakWeaponInfo.CurrentWeaponTag.IsValid())
	{
		return nullptr;
	}
	
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UWakPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	switch (ToggleDamageType)
	{
	case EToggleDamageType::CurrentEquippedWeapon:
		{
			const AWakWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();
			check(WeaponToToggle);

			UBoxComponent* WeaponCollisionComponent = WeaponToToggle->GetWeaponCollisionComponent();
			check(WeaponCollisionComponent);

			if (bShouldEnable)
			{
				WeaponCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			}
			else
			{
				WeaponCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				OverlappedActors.Empty();
			}

			break;
		}

	default:
		break;
	}
}

void UWakPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	unimplemented();
}

void UWakPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	// 무기가 타겟을 통과했을 때
	// 타격감을 위해 태그를 부여해 카메라 쉐이크를 주던지 뭔가 할 수 있음
	// 일단 기획에 뭐가 없어서 미구현
	unimplemented();
}
