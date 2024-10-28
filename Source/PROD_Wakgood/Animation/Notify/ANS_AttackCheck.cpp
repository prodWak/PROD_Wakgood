// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_AttackCheck.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WAKTag.h"
#include "Character/WakEnemyCharacter.h"
#include "Character/WAKTestCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/ITargetDevice.h"

void UANS_AttackCheck::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	AWAKTestCharacter* Character = Cast<AWAKTestCharacter>(MeshComp->GetOwner());
	if(Character)
	{
		//Character->SetWeaponOverlap(true);
		UE_LOG(LogTemp,Warning,TEXT("Character Weapon Overlap Is Activate"));
	}
}

void UANS_AttackCheck::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	AWAKTestCharacter* Character = Cast<AWAKTestCharacter>(MeshComp->GetOwner());
	if(Character)
	{
		//Character->SetWeaponOverlap(false);
		Character->NotifyEnd->Broadcast(); //Notify 종료. Ability에 HitAmount 초기화.
		UE_LOG(LogTemp,Warning,TEXT("Character Weapon Overlap Is DeActivate"));
		
	}
}

void UANS_AttackCheck::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	FGameplayEventData EventData;
	//Hit Detection
	AActor* Owner = MeshComp->GetOwner();
	AWAKTestCharacter* Character = Cast<AWAKTestCharacter>(Owner);

	
	if(Character == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("Owner is null"));
		//MeshComp->GetAnimInstance()->StopAllMontages(0);
	}
	else if(Character != nullptr && Character->WeaponCollision)
	{
		Character->WeaponCollision->GetOverlappingActors(Enemies,AWakEnemyCharacter::StaticClass());
		
		if(Enemies.Num() > 0)
		{
			for(auto Enemy : Enemies)
			{
				EventData.Instigator = Owner;
				EventData.EventTag = FWAKGameplayTags::Get().Event_Hit;
				EventData.ContextHandle = FGameplayEffectContextHandle();
				EventData.ContextHandle.AddInstigator(Owner,Owner);
					
				EventData.Target = Enemy;
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner,EventData.EventTag,EventData);
			}
		}
	}
	else if(Character->WeaponCollision == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("warning"));
	}
}
