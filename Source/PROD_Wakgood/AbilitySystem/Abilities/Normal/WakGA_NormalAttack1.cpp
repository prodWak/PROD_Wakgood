// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Normal/WakGA_NormalAttack1.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WAKTag.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameFramework/CharacterMovementComponent.h"

UWakGA_NormalAttack1::UWakGA_NormalAttack1()
{
	
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	StartUpTag = FWAKGameplayTags::Get().InputTag_Q;
	AbilityTags.AddTag(FWAKGameplayTags::Get().InputTag_Q);
	ActivationOwnedTags.AddTag(FWAKGameplayTags::Get().Action_IsAttacking);
	ActivationBlockedTags.AddTag(FWAKGameplayTags::Get().Action_IsAttacking);
	
	
	ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageFinder(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Slash.AM_Slash'"));
	if(AttackMontageFinder.Succeeded())
	{
		NormalAttackAnim = AttackMontageFinder.Object;
	}
	ConstructorHelpers::FClassFinder<UGameplayEffect> AttackEffectClass(TEXT("/Script/Engine.Blueprint'/Game/Ability/GameplayEffect/GE_Damage.GE_Damage_C'"));
	if(AttackEffectClass.Succeeded())
	{
		AttackEffect = AttackEffectClass.Class;	
	}
	MaxHitAmount = 1;
	
}

void UWakGA_NormalAttack1::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	check(AttackEffect);
	
	//OnNextAttackCheck.AddUObject(this,&UWakGA_NormalAttack1::NextAttackCheckDelegate);
	AWAKTestCharacter* Avatar = Cast<AWAKTestCharacter>(ActorInfo->AvatarActor);
	if(!Avatar->OnNextAttackCheck->IsBoundToObject(this))
		Avatar->OnNextAttackCheck->AddUObject(this,&UWakGA_NormalAttack1::NextAttackCheckDelegate);
	Avatar->GetCharacterMovement()->MaxWalkSpeed = 0.f;
	
	Avatar->GetCharacterMovement()->RotationRate = FRotator::ZeroRotator;

	if(OnNextAttackCheck.IsBound())
	{
		UE_LOG(LogTemp,Warning,TEXT("Bound"));
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("UnBound"));
	}
	WaitingHitEvent = WaitingEvent(); 
	AnimInstance = ActorInfo->GetAnimInstance();
	if(AnimInstance)
	{
		UE_LOG(LogTemp,Warning,TEXT("Attack Is Active"));
		//SetMontageCycle(AnimInstance,NormalAttackAnim);
		AnimInstance->Montage_Play(NormalAttackAnim);
		FOnMontageEnded MontageEndDelegate;
		MontageEndDelegate.BindUObject(this,&UWakGA_AttackBase::OnMontageEnd);
		AnimInstance->Montage_SetEndDelegate(MontageEndDelegate);
		
	}
}

void UWakGA_NormalAttack1::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	TObjectPtr<AWAKTestCharacter> Avatar = Cast<AWAKTestCharacter>(ActorInfo->AvatarActor);
	Avatar->GetCharacterMovement()->MaxWalkSpeed = 500.f;
	Avatar->GetCharacterMovement()->RotationRate = FRotator(0.f,500.f,0.f);
	WaitingHitEvent->EndTask();
	WaitingHitEvent->EventReceived.RemoveAll(this);
	HitAmount = 0;
	TargetResults.Empty();

	
}

void UWakGA_NormalAttack1::NextAttack()
{
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Input J in Ability"));
	if(isAbleNextAttack)
	{
		if(AnimInstance->Montage_IsPlaying(NormalAttackAnim))
		{
			FName CurrentSection = AnimInstance->Montage_GetCurrentSection(NormalAttackAnim);
			if(CurrentSection == FName("Attack1"))
			{
				AnimInstance->Montage_JumpToSection(FName("Attack2"),NormalAttackAnim);
			}
		}
	}
}


void UWakGA_NormalAttack1::NextAttackCheckDelegate(bool AbleNextAttack)
{
	isAbleNextAttack = AbleNextAttack;
	UE_LOG(LogTemp,Warning,TEXT("Called Function"));
}

void UWakGA_NormalAttack1::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	NextAttack();
}
