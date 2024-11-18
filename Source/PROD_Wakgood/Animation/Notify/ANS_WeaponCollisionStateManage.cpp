// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_WeaponCollisionStateManage.h"

#include "Character/WakEnemyCharacter.h"
#include "Character/WakPlayerCharacter.h"
#include "Components/CapsuleComponent.h"

void UANS_WeaponCollisionStateManage::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation,TotalDuration,EventReference);
	if(AWakPlayerCharacter* Player = Cast<AWakPlayerCharacter>(MeshComp->GetOwner()))
	{
		UE_LOG(LogTemp,Warning,TEXT("NotifyBegin"));
		Player->WeaponCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		TArray<AActor*> OverlappingActors;
		Player->WeaponCollision->GetOverlappingActors(OverlappingActors,AWakEnemyCharacter::StaticClass());
		for(AActor* OverlappingActor : OverlappingActors)
		{
			if(AWakEnemyCharacter* Enemy = Cast<AWakEnemyCharacter>(OverlappingActor))
			{
				Player->OverlappingActors.Add(Enemy,1);
			}
		}
	}
}

void UANS_WeaponCollisionStateManage::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if(AWakPlayerCharacter* Player = Cast<AWakPlayerCharacter>(MeshComp->GetOwner()))
	{
		Player->WeaponCollision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		Player->OverlappingActors.Empty();
		
	}

}
