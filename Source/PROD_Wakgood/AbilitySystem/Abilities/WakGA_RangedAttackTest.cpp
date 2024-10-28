// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WakGA_RangedAttackTest.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Actor/WakProjectile.h"

UWakGA_RangedAttackTest::UWakGA_RangedAttackTest()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ConstructorHelpers::FObjectFinder<UAnimMontage> HadoKenFinder(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Hadoken.AM_Hadoken'"));
	if(HadoKenFinder.Succeeded()) 
	{
		TestAnimMontage = HadoKenFinder.Object;	
	}

	ConstructorHelpers::FClassFinder<UGameplayEffect> AttackEffectClass(TEXT("/Script/Engine.Blueprint'/Game/Ability/GameplayEffect/GE_Damage.GE_Damage_C'"));
	if(AttackEffectClass.Succeeded())
	{
		AttackEffect = AttackEffectClass.Class;
		
	}
	MaxHitAmount = 1;
	ConstructorHelpers::FClassFinder<AWakProjectile> ProjectileFinder(TEXT("/Script/Engine.Blueprint'/Game/BP_WakProjectile.BP_WakProjectile_C'"));
	if(ProjectileFinder.Succeeded())
	{
		AbilityProjectileClass = ProjectileFinder.Class;
	}
	Damage = 5.f;
}

void UWakGA_RangedAttackTest::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	FHitCheckDelegate SpawnProjectileDelegate;
	FHitCheckDelegate HitCheckDelegate;
	SpawnProjectileDelegate.BindDynamic(this,&UWakGA_RangedAttackBase::SpawnProjectile);
	FireEvent = WaitingEventDynamic(SpawnProjectileDelegate,FWAKGameplayTags::Get().Event_Fire); // Montage에서 Fire 이벤트가 들어오면 투사체 발사.

	//1. Hit를 어빌리티에서 처리 
	/*
	HitCheckDelegate.BindDynamic(this,&UWakGA_AttackBase::OnAttackHit); //Hit하면 데미지 입힘.
	AttackEvent = WaitingEventDynamic(HitCheckDelegate,FWAKGameplayTags::Get().Event_ProjectileHit);
	*/

	//2. Hit를 Projectile에서 처리.
	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	FGameplayEffectSpecHandle HitEffectSpecHandle = SourceASC->MakeOutgoingSpec(AttackEffect,1,SourceASC->MakeEffectContext());
	
	const FWAKGameplayTags Tags = FWAKGameplayTags::Get();
	//Damage.GetValueAtLevel(GetAbilityLevel()); - 레벨에 따른 데미지 구하기
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(HitEffectSpecHandle ,Tags.Damage,Damage.Value); // Effect를 Set By Caller로 하고 이렇게 주면 됨.
	Projectile->HitEffectSpecHandle = HitEffectSpecHandle;
	
	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	//SetMontageCycle(AnimInstance,TestAnimMontage)
	if(AnimInstance)
	{
		UE_LOG(LogTemp,Warning,TEXT("RangedAttack Is Active"));
		//SetMontageCycle(AnimInstance,NormalAttackAnim);
		AnimInstance->Montage_Play(TestAnimMontage); //Montage의 Notify가 들어오면 Projectile 소환 
		FOnMontageEnded MontageEndDelegate;
		MontageEndDelegate.BindUObject(this,&UWakGA_AttackBase::OnMontageEnd);
		AnimInstance->Montage_SetEndDelegate(MontageEndDelegate);
	}
}

void UWakGA_RangedAttackTest::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	HitAmount = 0;
	HitResults.Empty();
	FireEvent->EndTask();
	FireEvent->EventReceived.RemoveAll(this);
	FireEvent = nullptr;
	AttackEvent->EndTask();
	AttackEvent->EventReceived.RemoveAll(this);
	AttackEvent = nullptr;
}
