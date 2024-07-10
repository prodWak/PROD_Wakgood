// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\WAKTag.h"
#include "GameplayTagsManager.h"
FWAKGameplayTags FWAKGameplayTags::WAKGameplayTags;
void FWAKGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
	//Character Form Tag
	WAKGameplayTags.Character_Form_Normal = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Normal"),FString("Current Form Normal"));
	WAKGameplayTags.Character_Form_Melee = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Melee"),FString("Current Form Melee"));
	WAKGameplayTags.Character_Form_Range = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.Range"),FString("Current Form Range"));
	WAKGameplayTags.Character_Form_LongRange = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Form.LongRange"),FString("Current Form LongRange"));
	//Input Tag
	WAKGameplayTags.InputTag_Q = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag.Q"),FString("Input Q"));
	WAKGameplayTags.InputTag_W = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag.W"),FString("Input Q"));
	WAKGameplayTags.InputTag_E = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag.E"),FString("Input Q"));
	WAKGameplayTags.InputTag_R = GameplayTagsManager.AddNativeGameplayTag(FName("InputTag.R"),FString("Input Q"));

	WAKGameplayTags.Type_Normal = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Type.Normal"),FString("Character Type Normal"));
	WAKGameplayTags.Type_Iron = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Type.Iron"),FString("Character Type Iron"));
	WAKGameplayTags.Type_Light = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Type.Iron"),FString("Character Type Iron"));
	WAKGameplayTags.Type_Water = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Type.Water"),FString("Character Type Water"));
	WAKGameplayTags.Type_Wind = GameplayTagsManager.AddNativeGameplayTag(FName("Character.Type.Wind"),FString("Character Type Wind"));
	
}
