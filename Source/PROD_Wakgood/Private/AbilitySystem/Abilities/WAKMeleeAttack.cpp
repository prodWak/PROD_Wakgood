// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\AbilitySystem\Abilities\WAKMeleeAttack.h"
#include "..\..\..\Public\WAKTag.h"
#include "..\..\..\Public\Character\WAKTestCharacter.h"

UWAKMeleeAttack::UWAKMeleeAttack()
{
	ActivationRequiredTags.AddTag(FWAKGameplayTags::Get().Character_Form_Melee);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

}

void UWAKMeleeAttack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Red,TEXT("Melee Attack Button Pressed"));
	// Attack Activate 되면 Anim Montage 재생. StaticMesh Collision 활성화
	// Static Mesh BeginOverlap시 해당 액터의 Type과 체력 저항력 가져옴. - Type 체크 - 데미지 계산 -
	// Health에 Effect 적용. 스태틱 메시 함수 종료.
	// Attack Montage 종료 - StaticMesh Collision 비활성화. EndAbility.
	
	check(AttackMotionAnimMontage);
	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	if(AnimInstance)
	{
		AnimInstance->Montage_Play(AttackMotionAnimMontage);
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this,&UWAKMeleeAttack::OnMontageComplete);
		AnimInstance->Montage_SetEndDelegate(EndDelegate);

		AWAKTestCharacter* GameCharacter = Cast<AWAKTestCharacter>(ActorInfo->AvatarActor);
		GameCharacter->SetWeaponOverlap(true);
	}
	
	
}

void UWAKMeleeAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UWAKMeleeAttack::OnMontageComplete(UAnimMontage* Montage, bool bInterrupted)
{
	
}

