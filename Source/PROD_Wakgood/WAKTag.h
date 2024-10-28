// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/**
 * 
 */

struct FWAKGameplayTags
{
private:
	static FWAKGameplayTags WAKGameplayTags;
public:
	static const FWAKGameplayTags& Get()
	{
		return WAKGameplayTags;
	}
	static void InitializeNativeGameplayTags();
	//태그 목록
	FGameplayTag Character_Form_Normal;
	FGameplayTag Character_Form_Sword;
	FGameplayTag Character_Form_Hammer;
	FGameplayTag Character_Form_Ninja;
	FGameplayTag Character_Form_Ranger;
	FGameplayTag Character_Form_Fighter;
	FGameplayTag Character_Form_Ice;
	FGameplayTag Character_Form_Fire;
	FGameplayTag Character_Form_Mic;
	FGameplayTag Character_Form_Spark;
	FGameplayTag Character_Form_Paper;

	FGameplayTag InputTag_Q;
	FGameplayTag InputTag_W;
	FGameplayTag InputTag_E;
	FGameplayTag InputTag_R;
	FGameplayTag InputTag_RMB;
	
	FGameplayTag Character_Type_Normal;
	FGameplayTag Character_Type_Water;
	FGameplayTag Character_Type_Iron;
	FGameplayTag Character_Type_Light;
	FGameplayTag Character_Type_Wind;

	FGameplayTag Event_Hit;
	FGameplayTag Event_Fire;
	FGameplayTag Event_ProjectileHit;

	FGameplayTag State_Stun;
	FGameplayTag Effects_HitReact;

	FGameplayTag Damage;

	//Ability Active Tag
	FGameplayTag Ability_FormChange_Normal;
	FGameplayTag Ability_FormChange_Sword;
	FGameplayTag Ability_FormChange_Hammer;
	FGameplayTag Ability_FormChange_Ninja;
	FGameplayTag Ability_FormChange_Ranger;
	FGameplayTag Ability_FormChange_Fighter;
	FGameplayTag Ability_FormChange_Ice;
	FGameplayTag Ability_FormChange_Fire;
	FGameplayTag Ability_FormChange_Mic;
	FGameplayTag Ability_FormChange_Spark;
	FGameplayTag Ability_FormChange_Paper;

	FGameplayTag Ability_Skill_1;
	FGameplayTag Ability_Skill_2;
	FGameplayTag Ability_Skill_3;
	FGameplayTag Ability_Skill_4;
	// 현재 행동
	FGameplayTag Action_IsJumping;
	FGameplayTag Action_IsAttacking;

	//Cue 관리
	FGameplayTag GameplayCue_Normal_Attack1;

	//Resistance
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;


};


 