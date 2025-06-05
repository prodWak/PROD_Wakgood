// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace WakGameplayTags
{
	PROD_WAKGOOD_API	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	// Declare all the custom native tags that Wak will use
	PROD_WAKGOOD_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	PROD_WAKGOOD_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);
	PROD_WAKGOOD_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Crouch);
	PROD_WAKGOOD_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_AutoRun);
	PROD_WAKGOOD_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack);
	PROD_WAKGOOD_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Pause);
	PROD_WAKGOOD_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Interaction);
	
	PROD_WAKGOOD_API    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Whip);
	PROD_WAKGOOD_API    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_DeathHammer);

	PROD_WAKGOOD_API    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Hit);

	PROD_WAKGOOD_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_BaseDamage);
};
