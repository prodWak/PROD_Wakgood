// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WakEnemyCharacter.h"

#include "AbilitySystem/WakAbilitySystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


void AWakEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//GetAbilitySystemComponent()->AddLooseGameplayTag(FormTag);
	//GetAbilitySystemComponent()->RegisterGameplayTagEvent(FWAKGameplayTags::Get().Effects_HitReact).AddUObject()
}


void AWakEnemyCharacter::InitializeAttributeToEffect()
{
	UWakAbilitySystemLibrary::InitializeDefaultAttributes(this,CharacterClass,Level,GetAbilitySystemComponent());	
}

void AWakEnemyCharacter::HitReact(FGameplayTag Tag, int32 NewCount)
{
	if(NewCount >= 1)
	{
		PlayAnimMontage(HitReactMontage);
		//멈추기, 아무 행동 하지 않기, 애니메이션 재생
		GetCharacterMovement()->StopActiveMovement();
		//LaunchCharacter(GetActorForwardVector() * -1.f * KnockBackDistance,true,false);
	}
	else if(NewCount <= 0)
	{
		StopAnimMontage(HitReactMontage);
		//GetLocalViewingPlayerController()->EnableInput(GetLocalViewingPlayerController());
	}

}

void AWakEnemyCharacter::Die()
{
}
