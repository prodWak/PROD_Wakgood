// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WAKDataTable.h"
#include "Abilities/GameplayAbility.h"
#include "WAKGA_FormChangeBase.generated.h"

class AWakPlayerState;
/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWAKGA_FormChangeBase : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UWAKGA_FormChangeBase();

	//자기 자신에게 능력치 이펙트 적용 - 

	//Form Tag 부여

	//외형 변경

	//GiveAbility
	
protected:
	FCharacterStatus* CharacterStatus;
	TObjectPtr<UDataTable> StatusData;
	//임시 캐릭터 명
	AWakPlayerState* TestPlayerState;
	void ChangeMesh(FString FormName);
	void ApplyFormBaseCharacterStatus(FString FormName);
	void GrantFormTag(FString FormName);
	void GiveSkillAbility(FString FormName);
	void ClearAbilityExceptThis();
	void SettingFormChange(FString FormName);
};
