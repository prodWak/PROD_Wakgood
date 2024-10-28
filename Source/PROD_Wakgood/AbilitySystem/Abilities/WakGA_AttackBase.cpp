// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WakGA_AttackBase.h"
#include "AbilitySystemComponent.h"
#include "WAKTag.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameplayCueManager.h"



void UWakGA_AttackBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	AWAKTestCharacter* Avatar = Cast<AWAKTestCharacter>(ActorInfo->AvatarActor);
	if(!Avatar->NotifyEnd->IsBoundToObject(this))
		Avatar->NotifyEnd->AddUObject(this,&UWakGA_AttackBase::InitHitAmount);
}

void UWakGA_AttackBase::BindHitEvent()
{
	UAbilitySystemComponent* ASC = GetActorInfo().AbilitySystemComponent.Get();
}

void UWakGA_AttackBase::PlayAttaackMontage(UAnimMontage* AttackMontage)
{
	UAnimInstance* CharacterAnim = CurrentActorInfo->AnimInstance.Get();
	CharacterAnim->Montage_Play(AttackAnimMontage); //애니메이션 안에 Notify State를 이용해서 Weapon의 Overlap을 켜주거나 꺼줌.
}

void UWakGA_AttackBase::FindEnemyInRange()
{
	//무기 메시에 Overlap 된 액터들 목록을 일단 전부 가져오기 Enemy액터 라면 Enemies에 저장
	AWAKTestCharacter* SourceCharacter = Cast<AWAKTestCharacter>(GetAvatarActorFromActorInfo());
	TArray<AActor*> EnemiesActor;
	SourceCharacter->Weapon->GetOverlappingActors(EnemiesActor,AWakEnemyCharacter::StaticClass());
	for(auto Enemy : EnemiesActor)
	{
		Enemies.AddUnique(Cast<AWakEnemyCharacter>(Enemy));
	}
}

void UWakGA_AttackBase::ApplyEffectToTargetSingle(TSubclassOf<UGameplayEffect> Effect, AWAKTestCharacter* Target)
{
	UAbilitySystemComponent* SourceAbilitySystem = CurrentActorInfo->AbilitySystemComponent.Get();
	FGameplayEffectContextHandle EffectContextHandle = SourceAbilitySystem->MakeEffectContext();
	EffectContextHandle.AddSourceObject(GetActorInfo().OwnerActor.Get());
	FGameplayEffectSpecHandle GameplayEffectSpecHandle = SourceAbilitySystem->MakeOutgoingSpec(Effect,1,EffectContextHandle);
	SourceAbilitySystem->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(),Target->GetAbilitySystemComponent());
	//float Health = Cast<UWAKAttributeSet>(Target->GetAbilitySystemComponent()->GetAttributeSet(UWAKAttributeSet::StaticClass()))->GetHealth();
}
void UWakGA_AttackBase::HitDetectionMelee()
{
	//Hit Detection
	
}

void UWakGA_AttackBase::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,false);
}

void UWakGA_AttackBase::SetMontageCycle(UAnimInstance* AnimInstance, UAnimMontage* AnimMontage)
{
	AnimInstance->Montage_Play(AnimMontage);
	FOnMontageEnded MontageEndDelegate;
	MontageEndDelegate.BindUObject(this,&UWakGA_AttackBase::OnMontageEnd);
	AnimInstance->Montage_SetEndDelegate(MontageEndDelegate);

}

void UWakGA_AttackBase::InitHitAmount()
{
	HitAmount = 0;
	UE_LOG(LogTemp,Warning,TEXT("Init Hit Amount 0"));
}


void UWakGA_AttackBase::OnAttackHit(FGameplayEventData Payload)
{
	check(AttackEffect);
	//현재까지 몇명을 때렸는지 체크 - 아직 X명 이하면 Effect 적용
	if(HitAmount < MaxHitAmount)
	{
		if(!TargetResults.Contains(Payload.Target))
		{
			//히트하지 않은 적에게만 공격
			AWAKTestCharacter* Target = Cast<AWAKTestCharacter>(Payload.Target);
			ApplyEffectToTargetSingle(AttackEffect,Target);
			Target->HealthCheck();
			//TargetResults.AddUnique(Target);
			HitAmount++;

			FGameplayCueParameters GameplayCueParameters;
			GameplayCueParameters.Location = Payload.Target->GetActorLocation();
			UGameplayCueManager::ExecuteGameplayCue_NonReplicated(Target,FWAKGameplayTags::Get().GameplayCue_Normal_Attack1,GameplayCueParameters); //테스트용 태그 사용중
		}
	}
}


UAbilityTask_WaitGameplayEvent* UWakGA_AttackBase::WaitingEvent()
{
	//Activate 부분에서 호출
	UAbilityTask_WaitGameplayEvent* WaitGameplayEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
	this,
	FWAKGameplayTags::Get().Event_Hit
	);
	WaitGameplayEvent->EventReceived.AddDynamic(this,&UWakGA_AttackBase::OnAttackHit);
	WaitGameplayEvent->ReadyForActivation();
	return WaitGameplayEvent;
}

UAbilityTask_WaitGameplayEvent* UWakGA_AttackBase::WaitingEventDynamic(FHitCheckDelegate Delegate, FGameplayTag RecivedTag)
{
	//위랑 다른 방법)
	UAbilityTask_WaitGameplayEvent* WaitGameplayEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
	this,
	RecivedTag//FWAKGameplayTags::Get().Event_Hit
	);
	WaitGameplayEvent->EventReceived.Add(Delegate);
	WaitGameplayEvent->ReadyForActivation();
	//WaitGameplayEvent->Activate();
	return WaitGameplayEvent;
}
