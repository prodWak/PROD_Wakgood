// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Normal/WakGA_NormalAttack1.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WAKTag.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Character/WakPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
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
	PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		FName("NormalMontage"),
		NormalAttackAnim,
		1,
		FName("Attack1")
		);
	

	PlayMontageAndWait->OnCompleted.AddUniqueDynamic(this,&UWakGA_NormalAttack1::OnMontageEnded);
	PlayMontageAndWait->OnBlendOut.AddUniqueDynamic(this,&UWakGA_NormalAttack1::OnMontageEnded);
	PlayMontageAndWait->OnCancelled.AddUniqueDynamic(this,&UWakGA_NormalAttack1::OnMontageEnded);
	PlayMontageAndWait->Activate();
	
	Avatar = Cast<AWAKTestCharacter>(ActorInfo->AvatarActor);
	
	if(!Avatar->OnNextAttackCheck->IsBoundToObject(this))
		Avatar->OnNextAttackCheck->AddUObject(this,&UWakGA_NormalAttack1::NextAttackCheckDelegate);

	Avatar->WeaponCollision->OnComponentBeginOverlap.AddUniqueDynamic(this,&UWakGA_NormalAttack1::ApplyDamageBeginOverlap);
	
	//
	
	Avatar->GetCharacterMovement()->MaxWalkSpeed = 0.f;
	Avatar->GetCharacterMovement()->RotationRate = FRotator::ZeroRotator;
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
	UE_LOG(LogTemp,Warning,TEXT("Ena Ability"))
	Avatar = Cast<AWAKTestCharacter>(ActorInfo->AvatarActor);
	Avatar->GetCharacterMovement()->MaxWalkSpeed = 500.f;
	Avatar->GetCharacterMovement()->RotationRate = FRotator(0.f,500.f,0.f);
	WaitingHitEvent->EndTask();
	WaitingHitEvent->EventReceived.RemoveAll(this);
	CurrentHitAmount = 0;
	HitAmount = 0;
	TargetResults.Empty();

	PlayMontageAndWait->OnCompleted.RemoveAll(this);
	PlayMontageAndWait->EndTask();

	Avatar->WeaponCollision->OnComponentBeginOverlap.RemoveDynamic(this,&UWakGA_NormalAttack1::ApplyDamageBeginOverlap);
	Enemies.Empty();
	HitEnemies.Empty();
	
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

void UWakGA_NormalAttack1::OnMontageEnded()
{
	EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,true);
}

void UWakGA_NormalAttack1::InputPressed(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	NextAttack();
}

void UWakGA_NormalAttack1::ApplyDamageBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
 	if(CurrentHitAmount < MaxHitAmount)
	{
		if(AWakEnemyCharacter* Enemy = Cast<AWakEnemyCharacter>(OtherActor))
		{
			if(!HitEnemies.Find(Enemy))
			{
				FGameplayEffectContextHandle EffectContext = Avatar->GetAbilitySystemComponent()->MakeEffectContext();
				FGameplayEffectSpecHandle EffectSpecHandle = Avatar->GetAbilitySystemComponent()->MakeOutgoingSpec(NormalAttackEffect,1,EffectContext);
				Avatar->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),Enemy->GetAbilitySystemComponent());

				FVector Direction = (Enemy->GetActorLocation() - Avatar->GetActorLocation()).GetSafeNormal();
				FVector LaunchVelocity = Direction * LaunchForce;
				LaunchVelocity.Z = 80.f;
				Enemy->LaunchCharacter(LaunchVelocity,false,false);

				HitEnemies.Add(Enemy,1);
			}
		}
	}
}

void UWakGA_NormalAttack1::KnokBack(AWakEnemyCharacter* Enemy, FVector TargetLocation)
{
	FVector CurrentEnemyLocation = Enemy->GetActorLocation();
	FVector InterpVector = FMath::VInterpTo(CurrentEnemyLocation,TargetLocation,GetWorld()->GetDeltaSeconds(),InterpSpeed);
	Enemy->SetActorLocation(InterpVector);
	if(FVector::Dist(Enemy->GetActorLocation(),TargetLocation) < 5.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(*KnockBackTimer);
	}
}
