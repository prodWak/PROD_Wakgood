// Fill out your copyright notice in the Description page of Project Settings.


#include "WAKTag.h"
#include "GameplayTagsManager.h"
FWAKGameplayTags FWAKGameplayTags::WAKGameplayTags;
void FWAKGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
	//Character Form Tag
	WAKGameplayTags.Character_Form_Normal = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Normal"),FString("Current Form Normal"));
	WAKGameplayTags.Character_Form_Sword = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Sword"),FString("Current Form Sword")); 
	WAKGameplayTags.Character_Form_Hammer= GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Hammer"),FString("Current Form Hammer"));
	WAKGameplayTags.Character_Form_Ninja= GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Ninja"),FString("Current Form Ninja"));
	WAKGameplayTags.Character_Form_Ranger= GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Ranger"),FString("Current Form Ranger"));
	WAKGameplayTags.Character_Form_Fighter= GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Fighter"),FString("Current Form Fighter"));
	WAKGameplayTags.Character_Form_Ice= GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Ice"),FString("Current Form Ice"));
	WAKGameplayTags.Character_Form_Fire= GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Fire"),FString("Current Form Fire"));
	WAKGameplayTags.Character_Form_Mic= GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Mic"),FString("Current Form Mic"));
	WAKGameplayTags.Character_Form_Spark= GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Spark"),FString("Current Form Spark"));
	WAKGameplayTags.Character_Form_Paper= GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Paper"),FString("Current Form Paper"));

	
	//Input Tag
	WAKGameplayTags.InputTag_Q = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag.Q"),FString("Input Q"));
	WAKGameplayTags.InputTag_W = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag.W"),FString("Input Q"));
	WAKGameplayTags.InputTag_E = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag.E"),FString("Input Q"));
	WAKGameplayTags.InputTag_R = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag.R"),FString("Input Q"));
	WAKGameplayTags.InputTag_RMB = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag.RMB"),FString("Input LMB"));

	WAKGameplayTags.Character_Type_Normal = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Type.Normal"),FString("Character Type Normal"));
	WAKGameplayTags.Character_Type_Iron = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Type.Iron"),FString("Character Type Iron"));
	WAKGameplayTags.Character_Type_Light = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Type.Light"),FString("Character Type Light"));
	WAKGameplayTags.Character_Type_Water = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Type.Water"),FString("Character Type Water"));
	WAKGameplayTags.Character_Type_Wind = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Type.Wind"),FString("Character Type Wind"));

	//Event Tag
	WAKGameplayTags.Event_Hit = GameplayTagsManager.AddNativeGameplayTag(FName("Event.Hit"),FString("Event Hit"));
	WAKGameplayTags.Event_Fire = GameplayTagsManager.AddNativeGameplayTag(FName("Event.Fire"),FString("Event Fire"));
	WAKGameplayTags.Event_ProjectileHit = GameplayTagsManager.AddNativeGameplayTag(FName("Event.ProjectileHit"),FString("Event ProjectileHit"));
	//State 
	WAKGameplayTags.State_Stun = GameplayTagsManager.AddNativeGameplayTag(FName("State.Stun"),FString("State Stun"));
	WAKGameplayTags.Effects_HitReact = GameplayTagsManager.AddNativeGameplayTag(FName("Effects.HitReact"),FString("Tag Granted When Hit Reacting"));

	WAKGameplayTags.Damage = GameplayTagsManager.AddNativeGameplayTag(FName("Damage"),FString("Damage"));

	//Ability Active Tag
	WAKGameplayTags.Ability_FormChange_Normal = GameplayTagsManager.AddNativeGameplayTag(FName("Ability.FormChange.Normal"),FString("Activate Ability Form Change To Normal"));
	WAKGameplayTags.Ability_FormChange_Sword = GameplayTagsManager.AddNativeGameplayTag(FName("Ability.FormChange.Sword"),FString("Activate Ability Form Change To Sword")); 
	WAKGameplayTags.Ability_FormChange_Hammer= GameplayTagsManager.AddNativeGameplayTag(FName("Ability.FormChange.Hammer"),FString("Activate Ability Form Change To Hammer"));
	WAKGameplayTags.Ability_FormChange_Ninja= GameplayTagsManager.AddNativeGameplayTag(FName("Ability.FormChange.Ninja"),FString("Activate Ability Form Change To Ninja"));
	WAKGameplayTags.Ability_FormChange_Ranger= GameplayTagsManager.AddNativeGameplayTag(FName("Ability.FormChange.Ranger"),FString("Activate Ability Form Change To Ranger"));
	WAKGameplayTags.Ability_FormChange_Fighter= GameplayTagsManager.AddNativeGameplayTag(FName("Ability.FormChange.Fighter"),FString("Activate Ability Form Change To Fighter"));
	WAKGameplayTags.Ability_FormChange_Ice= GameplayTagsManager.AddNativeGameplayTag(FName("Ability.FormChange.Ice"),FString("Activate Ability Form Change To Ice"));
	WAKGameplayTags.Ability_FormChange_Fire= GameplayTagsManager.AddNativeGameplayTag(FName("Ability.FormChange.Fire"),FString("Activate Ability Form Change To Fire"));
	WAKGameplayTags.Ability_FormChange_Mic= GameplayTagsManager.AddNativeGameplayTag(FName("Ability.FormChange.Mic"),FString("Activate Ability Form Change To Mic"));
	WAKGameplayTags.Ability_FormChange_Spark= GameplayTagsManager.AddNativeGameplayTag(FName("Ability.FormChange.Spark"),FString("Activate Ability Form Change To Spark"));
	WAKGameplayTags.Ability_FormChange_Paper= GameplayTagsManager.AddNativeGameplayTag(FName("Ability.FormChange.Paper"),FString("Activate Ability Form Change To Paper"));

	WAKGameplayTags.Ability_Skill_1 = GameplayTagsManager.AddNativeGameplayTag(FName("Ability.Skill.1"),FString("Active Skill 1"));
	WAKGameplayTags.Ability_Skill_2 = GameplayTagsManager.AddNativeGameplayTag(FName("Ability.Skill.2"),FString("Active Skill 2"));
	WAKGameplayTags.Ability_Skill_3 = GameplayTagsManager.AddNativeGameplayTag(FName("Ability.Skill.3"),FString("Active Skill 3"));
	WAKGameplayTags.Ability_Skill_4 = GameplayTagsManager.AddNativeGameplayTag(FName("Ability.Skill.4"),FString("Active Skill 4"));
	
	WAKGameplayTags.Action_IsJumping = GameplayTagsManager.AddNativeGameplayTag(FName("Action.IsJumping"),FString("Character Is Now Jumping"));
	WAKGameplayTags.Action_IsAttacking = GameplayTagsManager.AddNativeGameplayTag(FName("Action.IsAttacking"),FString("Character Is Now Attacking"));

	WAKGameplayTags.GameplayCue_Normal_Attack1 = GameplayTagsManager.AddNativeGameplayTag(FName("GameplayCue.Normal.Attack1"),FString("Play Effect For Normal Attack1"));
//	WAKGameplayTags.DamageTypesToResistances.Add()

	
}
