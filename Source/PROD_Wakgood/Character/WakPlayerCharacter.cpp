// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WakPlayerCharacter.h"

#include "Input/WAKInputComponent.h"
#include "AbilitySystem/WAKASC.h"
#include "Player/WakPlayerState.h"

AWakPlayerCharacter::AWakPlayerCharacter()
{
	
}



void AWakPlayerCharacter::PossessedBy(AController* NewController)
{
	ASC = CastChecked<UWAKASC>(GetPlayerState<AWakPlayerState>()->GetAbilitySystemComponent());
	ASC->InitAbilityActorInfo(GetPlayerState(),this);
	AttributeSet = GetPlayerState<AWakPlayerState>()->GetAttributeSet();
	ASC->AddLooseGameplayTag(FWAKGameplayTags::Get().Character_Form_Normal);
	ASC->CurrentFormTag = FWAKGameplayTags::Get().Character_Form_Normal;
	InitializeAttributeToEffect();
}


void AWakPlayerCharacter::Die()
{
	SetLifeSpan(Lifespan);
	Super::Die();
}



