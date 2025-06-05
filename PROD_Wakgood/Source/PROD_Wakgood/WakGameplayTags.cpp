// Copyright Epic Games, Inc. All Rights Reserved.

#include "WakGameplayTags.h"

#include "Engine/EngineTypes.h"
#include "GameplayTagsManager.h"
#include "WakLogChannels.h"

namespace WakGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Move, "InputTag.Move", "Move input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Jump, "InputTag.Jump", "Jump input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Crouch, "InputTag.Crouch", "Crouch input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_AutoRun, "InputTag.AutoRun", "Auto-run input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Attack, "InputTag.Attack", "Attack input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Pause, "InputTag.Pause", "Pause input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Interaction, "InputTag.Interaction", "Interaction input.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Weapon_Whip, "Weapon.Whip", "Wak's primary weapon 'whip'.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Weapon_DeathHammer, "Weapon.DeathHammer", "Shared weapon 'DeathHammer'.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Hit, "Event.Hit", "Send GameplayEvent Actor 'Hit'.")

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(SetByCaller_BaseDamage, "SetByCaller.BaseDamage", "SetByCaller BaseDamage");
	
	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString)
	{
		const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

		if (!Tag.IsValid() && bMatchPartialString)
		{
			FGameplayTagContainer AllTags;
			Manager.RequestAllGameplayTags(AllTags, true);

			for (const FGameplayTag& TestTag : AllTags)
			{
				if (TestTag.ToString().Contains(TagString))
				{
					UE_LOG(LogWak, Display, TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."), *TagString, *TestTag.ToString());
					Tag = TestTag;
					break;
				}
			}
		}

		return Tag;
	}
}

