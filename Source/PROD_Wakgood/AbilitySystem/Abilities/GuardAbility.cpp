// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardAbility.h"
#include "Components/BoxComponent.h"
#include "Character/WakPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UGuardAbility::UGuardAbility()
{
	
}

void UGuardAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	PlayerShiled = Cast<AWakPlayerCharacter>(GetAvatarActorFromActorInfo())->Shiled;
	PlayerShiled->SetActive(true);
	PlayerShiled->OnComponentBeginOverlap.AddUniqueDynamic(this,&UGuardAbility::ShileOverlap);
	Cast<AWakPlayerCharacter>(GetAvatarActorFromActorInfo())->GetCharacterMovement()->MaxWalkSpeed = 0.f;
	Cast<AWakPlayerCharacter>(GetAvatarActorFromActorInfo())->GetCharacterMovement()->RotationRate = FRotator::ZeroRotator;
	CommitAbility(Handle,ActorInfo,ActivationInfo);
	ApplyGameplayEffectToOwner(Handle,ActorInfo,ActivationInfo,GuardEffectClass.GetDefaultObject(),1);
    BlockTagDelegateHandle = GetAbilitySystemComponentFromActorInfo()->RegisterGameplayTagEvent(FWAKGameplayTags::Get().Action_IsBlocking,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&UGuardAbility::OnRemoveBlockingTag);
	//Animation 재생

	//
	EndAbility(Handle,ActorInfo,ActivationInfo,true,true);
	
//UGameplayTask_TagRemoved
	//Gameplay Effect 적용
}

void UGuardAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UE_LOG(LogTemp,Warning,TEXT("EndAbility"));
	GetAbilitySystemComponentFromActorInfo()->UnregisterGameplayTagEvent(BlockTagDelegateHandle,FWAKGameplayTags::Get().Action_IsBlocking,EGameplayTagEventType::NewOrRemoved);

	Cast<AWakPlayerCharacter>(GetAvatarActorFromActorInfo())->GetCharacterMovement()->MaxWalkSpeed = Cast<AWakPlayerCharacter>(GetAvatarActorFromActorInfo())->BaseWalkSpeed;
	Cast<AWakPlayerCharacter>(GetAvatarActorFromActorInfo())->GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	BlockTagDelegateHandle.Reset();
}

void UGuardAbility::OnRemoveBlockingTag(const FGameplayTag CallbackTag, int32 NewCount)
{
	if(CallbackTag == FWAKGameplayTags::Get().Action_IsBlocking)
	{
		if(NewCount <= 0)
		{
			EndAbility(GetCurrentAbilitySpecHandle(),GetCurrentActorInfo(),GetCurrentActivationInfo(),true,true);
		}
	}
}

void UGuardAbility::ShileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Case1 투사체: 투사체를 제거.

	//Case2 근접 공격 당할 시?

	//Case3 몸통박치기 시?

	
}
