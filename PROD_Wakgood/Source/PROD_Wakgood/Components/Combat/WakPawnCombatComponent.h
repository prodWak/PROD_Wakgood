// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WakGameplayTags.h"
#include "Components/WakPawnExtensionComponent.h"
#include "WakPawnCombatComponent.generated.h"

class AWakWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon
};

USTRUCT(BlueprintType)
struct FWakWeaponInfo
{
	GENERATED_BODY()

	/** 현재 장착한 무기 추적용 태그
	 *  Enemy의 경우 자동으로 설정됨
	 *  Player의 경우 BP에서 수동으로 설정해줘야 함
	 *  무기를 장착할 때 이 태그를 수동으로 설정하고,
	 *  무기를 해제할 때 수동으로 지워햐 함
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Wak|Combat")
	FGameplayTag CurrentWeaponTag;

	UPROPERTY(BlueprintReadOnly, Category = "Wak|Combat")
	TObjectPtr<AWakWeaponBase> WakWeapon;
};

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakPawnCombatComponent : public UWakPawnExtensionComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Wak|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
	// 무기 스폰 후 등록
	UFUNCTION(BlueprintCallable, Category = "Wak|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWakWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Wak|Combat")
	void SetWeaponInfo(FGameplayTag InWeaponTagToChange, AWakWeaponBase* InWeaponToChange);
	
	UFUNCTION(BlueprintCallable, Category = "Wak|Combat")
	AWakWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category = "Wak|Combat")
	AWakWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Wak|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
	UPROPERTY()
	TArray<AActor*> OverlappedActors;
	
private:
	UPROPERTY(BlueprintReadOnly, Category = "Wak|Combat", meta = (AllowPrivateAccess = "true"))
	FWakWeaponInfo WakWeaponInfo;
};
