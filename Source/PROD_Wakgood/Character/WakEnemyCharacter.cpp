// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WakEnemyCharacter.h"

#include "AbilitySystem/WakAbilitySystemLibrary.h"


void AWakEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//GetAbilitySystemComponent()->AddLooseGameplayTag(FormTag);
}

void AWakEnemyCharacter::InitializeAttributeToEffect()
{
	UWakAbilitySystemLibrary::InitializeDefaultAttributes(this,CharacterClass,Level,GetAbilitySystemComponent());	
}
