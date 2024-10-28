// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Normal/WakGA_Catch.h"
#include "WAKTag.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystem/Abilities/Normal/WAKGA_FormChangeNormal.h"

UWakGA_Catch::UWakGA_Catch()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	SourceRequiredTags.AddTag(FWAKGameplayTags::Get().Character_Form_Normal);
	ConstructorHelpers::FObjectFinder<UAnimMontage> CatchMontageFinder(TEXT("/Script/Engine.AnimMontage'/Game/Characters/Mannequins/Animations/Manny/AM_Experiment12.AM_Experiment12'"));
	if(CatchMontageFinder.Succeeded())
	{
		CatchAttackAnim = CatchMontageFinder.Object;
	}
	// 다른 이펙트를 만들어야 함.
	ConstructorHelpers::FClassFinder<UGameplayEffect> AttackEffectClass(TEXT("/Script/Engine.Blueprint'/Game/Ability/GameplayEffect/GE_Damage.GE_Damage_C'"));
	if(AttackEffectClass.Succeeded())
	{
		AttackEffect = AttackEffectClass.Class;
		// AttackEffect를 Catch용으로 무조건 체력을 0으로 만드는 Effect를 만들어서 세팅. 
	}
	MaxHitAmount = 1;

}

void UWakGA_Catch::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//애니메이션 재생, 타겟 가져오기, 타겟의 Tag 가져오기, DataTable에서 Tag와 맞는 Row를 찾아서 FormChange_X 어빌리티 실행.
	check(AttackEffect);
	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	HitDelegate.BindDynamic(this,&UWakGA_Catch::AbsorbEnemy);
//	HitDelegate.BindUFunction(this,TEXT("AbsorbEnemy"));
	WaitingEventDynamic(HitDelegate, FWAKGameplayTags::Get().Event_Hit);
	
	if(AnimInstance)
	{
		//SetMontageCycle(AnimInstance,CatchAttackAnim);
		AnimInstance->Montage_Play(CatchAttackAnim);
		FOnMontageEnded MontageEndDelegate;
		MontageEndDelegate.BindUObject(this,&UWakGA_AttackBase::OnMontageEnd);
		AnimInstance->Montage_SetEndDelegate(MontageEndDelegate);

	}
}

void UWakGA_Catch::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	HitAmount = 0;
	TargetResults.Empty();
}

void UWakGA_Catch::AbsorbEnemy(FGameplayEventData Payload)
{
	//check(AttackEffect);
	//현재까지 몇명을 때렸는지 체크 - 아직 X명 이하면 Effect 적용
	if(HitAmount < MaxHitAmount)
	{
		if(!TargetResults.Contains(Payload.Target))
		{
			//히트하지 않은 적에게만 공격
			AWAKTestCharacter* Target = Cast<AWAKTestCharacter>(Payload.Target);
			TargetResults.AddUnique(Target);
			HitAmount++;
			ChangeFormByEnemyTag(Target);
		}
	}

}

void UWakGA_Catch::ChangeFormByEnemyTag(AWAKTestCharacter* Target)
{
	UAbilitySystemComponent* TargetAbility = Target->GetAbilitySystemComponent();
	if(TargetAbility->HasMatchingGameplayTag(FWAKGameplayTags::Get().Character_Form_Normal))
	{
		FGameplayAbilitySpec GameplayAbilitySpec(UWAKGA_FormChangeNormal::StaticClass());
		GameplayAbilitySpec.SourceObject = CurrentActorInfo->AvatarActor;
		CurrentActorInfo->AbilitySystemComponent->GiveAbilityAndActivateOnce(GameplayAbilitySpec);
	}
	else if(TargetAbility->HasMatchingGameplayTag(FWAKGameplayTags::Get().Character_Form_Fire))
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("Change Form Fire"));
	}
	else if(TargetAbility->HasMatchingGameplayTag(FWAKGameplayTags::Get().Character_Form_Hammer))
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("Change Form Hammer"));
	}
	else if(TargetAbility->HasMatchingGameplayTag(FWAKGameplayTags::Get().Character_Form_Fighter))
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("Change Form Fighter"));
	}
	else if(TargetAbility->HasMatchingGameplayTag(FWAKGameplayTags::Get().Character_Form_Ice))
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("Change Form Ice"));
	}
	else if(TargetAbility->HasMatchingGameplayTag(FWAKGameplayTags::Get().Character_Form_Mic))
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("Change Form Mic"));
	}
	else if(TargetAbility->HasMatchingGameplayTag(FWAKGameplayTags::Get().Character_Form_Ninja))
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("Change Form Ninja"));
	}
	else if(TargetAbility->HasMatchingGameplayTag(FWAKGameplayTags::Get().Character_Form_Paper))
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("Change Form Paper"));
	}
	else if(TargetAbility->HasMatchingGameplayTag(FWAKGameplayTags::Get().Character_Form_Ranger))
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("Change Form Ranger"));
	}
	else if(TargetAbility->HasMatchingGameplayTag(FWAKGameplayTags::Get().Character_Form_Spark))
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("Change Form Spark"));
	}
	else if(TargetAbility->HasMatchingGameplayTag(FWAKGameplayTags::Get().Character_Form_Sword))
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("Change Form Sword"));
	}
	
}
