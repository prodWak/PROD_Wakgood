// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_NextAttackCheck.h"

void UANS_NextAttackCheck::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if(Cast<AWAKTestCharacter>(MeshComp->GetOwner()))
	{
		Cast<AWAKTestCharacter>(MeshComp->GetOwner())->OnNextAttackCheck->Broadcast(true);
	}
		
	//OnNextAttackCheck.Broadcast(true);
}

void UANS_NextAttackCheck::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if(Cast<AWAKTestCharacter>(MeshComp->GetOwner()))
	{
		Cast<AWAKTestCharacter>(MeshComp->GetOwner())->OnNextAttackCheck->Broadcast(false);
	}
	//OnNextAttackCheck.Broadcast(false);
	
}
