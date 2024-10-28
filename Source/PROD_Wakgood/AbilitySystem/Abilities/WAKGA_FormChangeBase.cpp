// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WAKGA_FormChangeBase.h"

#include "AbilitySystem/WAKAttributeSet.h"
#include "Player/WakPlayerState.h"
#include "Character/WAKTestCharacter.h"

UWAKGA_FormChangeBase::UWAKGA_FormChangeBase()
{
	ConstructorHelpers::FObjectFinder<UDataTable> StatusObjectFinder(TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_CharacterStatus.DT_CharacterStatus'"));
	if(StatusObjectFinder.Succeeded())
	{
		StatusData = StatusObjectFinder.Object;
	}
}

void UWAKGA_FormChangeBase::ChangeMesh(FString FormName)
{
	// Player Form에 맞춰서 Mesh변경.
	CharacterStatus = StatusData->FindRow<FCharacterStatus>(FName(FormName),FString("Character Status Context"));

	//변경.
}

void UWAKGA_FormChangeBase::ApplyFormBaseCharacterStatus(FString FormName)
{
	CharacterStatus = StatusData->FindRow<FCharacterStatus>(FName(FormName),FString("Character Status Context"));
	UWAKAttributeSet* PlayerAttributeSet = Cast<AWAKTestCharacter>(GetAvatarActorFromActorInfo())->GetAttributeSet(); 
	PlayerAttributeSet->SetHealth(CharacterStatus->Health);
	PlayerAttributeSet->SetMaxHealth(CharacterStatus->MaxHealth);
	PlayerAttributeSet->SetDamage(CharacterStatus->Damage);
	PlayerAttributeSet->SetResist(CharacterStatus->Resist);
	
}

void UWAKGA_FormChangeBase::GrantFormTag(FString FormName)
{
	CharacterStatus = StatusData->FindRow<FCharacterStatus>(FName(FormName),FString("Character Status Context"));
	//폼 태그
	FGameplayTagContainer Tags;
	CurrentActorInfo->AbilitySystemComponent->GetOwnedGameplayTags(Tags);
	CurrentActorInfo->AbilitySystemComponent->RemoveLooseGameplayTags(Tags);
	CurrentActorInfo->AbilitySystemComponent->AddLooseGameplayTag(CharacterStatus->FormTag);
	CurrentActorInfo->AbilitySystemComponent->AddLooseGameplayTag(CharacterStatus->TypeTag);
}

void UWAKGA_FormChangeBase::GiveSkillAbility(FString FormName)
{
	CharacterStatus = StatusData->FindRow<FCharacterStatus>(FName(FormName),FString("Character Status Context"));
	
	for(TTuple<TSubclassOf<UGameplayAbility>, FGameplayTag>& Ability : CharacterStatus->MoveSet)
	{
		CurrentActorInfo->AbilitySystemComponent->GiveAbility(Ability.Key);	
	}
}

void UWAKGA_FormChangeBase::ClearAbilityExceptThis()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	TArray<FGameplayAbilitySpecHandle> OutAbilityHandles;
	ASC->GetAllAbilities(OutAbilityHandles);
	OutAbilityHandles.Remove(GetCurrentAbilitySpecHandle());
	for(auto Handle : OutAbilityHandles)
	{
		ASC->ClearAbility(Handle);
	}
}

void UWAKGA_FormChangeBase::SettingFormChange(FString FormName)
{
	ClearAbilityExceptThis();
	//ChangeMesh(FormName);
	ApplyFormBaseCharacterStatus(FormName);
	GrantFormTag(FormName);
	GiveSkillAbility(FormName);
	
}
