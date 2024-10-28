// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WakGA_HitReact.h"

#include "WAKTag.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/WAKTestCharacter.h"

UWakGA_HitReact::UWakGA_HitReact()
{
	AbilityTags.AddTag(FWAKGameplayTags::Get().Effects_HitReact);
	ConstructorHelpers::FObjectFinder<UGameplayEffect> EffectFinder(TEXT(""));
	if(EffectFinder.Succeeded())
		HitReactEffect = EffectFinder.Object;
}

void UWakGA_HitReact::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	AWAKTestCharacter* SourceCharacter = Cast<AWAKTestCharacter>(GetAvatarActorFromActorInfo());
	check(SourceCharacter->GetReactMontage());
	ActiveEffectHitReact = ApplyGameplayEffectToOwner(Handle,ActorInfo,ActivationInfo,HitReactEffect,1);
	
	PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
	this,
	TEXT("None"),
	SourceCharacter->GetReactMontage()	
	);
	PlayMontageAndWait->OnCompleted.AddUniqueDynamic(this,&UWakGA_HitReact::OnMontageEnded);
	PlayMontageAndWait->OnInterrupted.AddUniqueDynamic(this,&UWakGA_HitReact::OnMontageEnded);
	PlayMontageAndWait->OnCancelled.AddUniqueDynamic(this,&UWakGA_HitReact::OnMontageEnded);
}
void UWakGA_HitReact::OnMontageEnded()
{
	GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(ActiveEffectHitReact);
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,false);
}
void UWakGA_HitReact::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

