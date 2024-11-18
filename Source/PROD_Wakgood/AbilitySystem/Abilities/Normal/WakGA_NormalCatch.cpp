// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Normal/WakGA_NormalCatch.h"

#include "Character/WakPlayerCharacter.h"
#include "Components/CapsuleComponent.h"

UWakGA_NormalCatch::UWakGA_NormalCatch()
{
	StartUpTag = FWAKGameplayTags::Get().InputTag_W;
	AbilityTags.AddTag(FWAKGameplayTags::Get().InputTag_W);
}

void UWakGA_NormalCatch::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UE_LOG(LogTemp,Warning,TEXT("Activate Normal Catch"));
	Avatar = Cast<AWakPlayerCharacter>(GetAvatarActorFromActorInfo());
	Avatar->WeaponCollision->OnComponentBeginOverlap.AddUniqueDynamic(this,&UWakGA_NormalCatch::GrabEnemy);
	
	//히트(완료) - Character 앞으로 끌고옴(완료) - Binding Tag 부여(Effect에서 부여) - 이 상태에서 특정 키 누르면 흡수 
}

void UWakGA_NormalCatch::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UWakGA_NormalCatch::ApplyEffectToTarget()
{
	FGameplayEffectContextHandle EffectContextHandle = Avatar->GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(Avatar);
	FGameplayEffectSpecHandle EffectSpecHandle = Avatar->GetAbilitySystemComponent()->MakeOutgoingSpec(CatchEffect,1,EffectContextHandle);
	Avatar->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),Enemy->GetAbilitySystemComponent());
}

void UWakGA_NormalCatch::GrabEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(AWakEnemyCharacter*  OverlapActor = Cast<AWakEnemyCharacter>(OtherActor))
	{
		Enemy = OverlapActor;
		TWeakObjectPtr<AWakEnemyCharacter> InEnemy;
		FVector TargetLocation = Avatar->GetActorForwardVector();
		TargetLocation.Y = TargetLocation.Y + 100.f;
		
		FRotator EnemyRotation = (Avatar->GetActorLocation() - Enemy->GetActorLocation()).Rotation();
		Enemy->SetActorRotation(EnemyRotation);
		ApplyEffectToTarget();
		//앞으로 자연스럽게 끌고와야함.
		FTimerHandle GrabTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(GrabTimerHandle,FTimerDelegate::CreateLambda([this,InEnemy,TargetLocation,&GrabTimerHandle]()
		{
			FVector CurrentEnemyLocation = InEnemy->GetActorLocation();
			FVector MoveVector = FMath::VInterpTo(CurrentEnemyLocation,TargetLocation,GetWorld()->GetDeltaSeconds(),InterpSpeed);
			InEnemy->SetActorLocation(MoveVector);
			if(FVector::Dist(InEnemy->GetActorLocation(),TargetLocation) <= 1.f)
			{
				GetWorld()->GetTimerManager().ClearTimer(GrabTimerHandle);
			}
		}),0.01f,true);
	}
}
