// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\AbilitySystem\Abilities\WAKGA_Normal.h"

#include "..\..\..\Public\Character\WAKTestCharacter.h"


UWAKGA_Normal::UWAKGA_Normal()
{
    //AbilityTags.AddTag(FWAKGameplayTags::Get().Character_Form_Normal);
}

void UWAKGA_Normal::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    UE_LOG(LogTemp,Warning,TEXT("Normal Form Tag : %s"),*FWAKGameplayTags::Get().Character_Form_Normal.ToString());

}


 

