// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_FireProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WAKTag.h"

void UAN_FireProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	UE_LOG(LogTemp,Warning,TEXT("Notify Is Called"));
	FGameplayEventData Payload;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		MeshComp->GetOwner(),
		FWAKGameplayTags::Get().Event_Fire,
		Payload
	); //WakGA_RangedAttackTest에서 이벤트를 받음. 
}
