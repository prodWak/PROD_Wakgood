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
	FGameplayTag Character_Form_Melee;
	FGameplayTag Character_Form_Range;
	FGameplayTag Character_Form_LongRange;

	FGameplayTag InputTag_Q;
	FGameplayTag InputTag_W;
	FGameplayTag InputTag_E;
	FGameplayTag InputTag_R;

	FGameplayTag Type_Normal;
	FGameplayTag Type_Water;
	FGameplayTag Type_Iron;
	FGameplayTag Type_Light;
	FGameplayTag Type_Wind;
	
};


 