// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WakGameplayTags.h"
#include "Components/WakPawnExtensionComponent.h"
#include "WakPawnCombatComponent.generated.h"

class AWakWeaponBase;

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
	FGameplayTag CurrentEquippedWeaponTag;

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

	/*
	 * 지금은 스폰하자마자 무기를 부여하지만,
	 * 먼가 튜토리얼 후에 무기를 부여하는식으로 갈 것 같으니까 나중에 수정해야댐
	 */
	
	// 무기 스폰 후 등록
	UFUNCTION(BlueprintCallable, Category = "Wak|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWakWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	// 변신할 때 사용
	UFUNCTION(BlueprintCallable, Category = "Wak|Combat")
	void SetWeaponInfo(FGameplayTag InWeaponTagToChange, AWakWeaponBase* InWeaponToChange);
	
	UFUNCTION(BlueprintCallable, Category = "Wak|Combat")
	AWakWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category = "Wak|Combat")
	AWakWeaponBase* GetCharacterCurrentEquippedWeapon() const;
	
private:
	UPROPERTY(BlueprintReadOnly, Category = "Wak|Combat", meta = (AllowPrivateAccess = "true"))
	FWakWeaponInfo WakWeaponInfo;
	
};
