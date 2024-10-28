// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Character/WakEnemyCharacter.h"
#include "WakGA_AttackBase.generated.h"
DECLARE_DYNAMIC_DELEGATE_OneParam(FHitCheckDelegate, FGameplayEventData, Payload);
/**
 * 
 */
class UAbilityTask_WaitGameplayEvent;
UCLASS()
class PROD_WAKGOOD_API UWakGA_AttackBase : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	AActor* Character; // Activate 시점에 설정되어야 함.  , 클래스명은 바꿔야 함.
	UPROPERTY()
	TArray<AWakEnemyCharacter*> Enemies;
	UPROPERTY()
	UAnimMontage* AttackAnimMontage;

	
	
	UFUNCTION()
	void PlayAttaackMontage(UAnimMontage* AttackMontage);
	UFUNCTION()
	void FindEnemyInRange();
	UFUNCTION()
	void ApplyEffectToTargetSingle(TSubclassOf<UGameplayEffect> Effect, AWAKTestCharacter* Target);
	//UFUNCTION()
	//void ApplyEffectToTargetMulti(TSubclassOf<UGameplayEffect> Effect, int8 TargetAmount);
	UFUNCTION()
	void HitDetectionMelee();
	UFUNCTION()
	void BindHitEvent();
	
	
	UFUNCTION()
	UAbilityTask_WaitGameplayEvent* WaitingEvent();

	UAbilityTask_WaitGameplayEvent* WaitingEventDynamic(FHitCheckDelegate Delegate, FGameplayTag RecivedTag);

	UPROPERTY(VisibleAnywhere)
	TArray<FHitResult> HitResults;

	UPROPERTY(VisibleAnywhere)
	TArray<AWAKTestCharacter*> TargetResults;

	UPROPERTY()
	int8 HitAmount = 0;

	UPROPERTY()
	int8 MaxHitAmount = 0;

	UPROPERTY()
	TSubclassOf<UGameplayEffect> AttackEffect;

	UPROPERTY(EditAnywhere, Category="Damage")
	FScalableFloat Damage;
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UFUNCTION()
	void OnAttackHit(FGameplayEventData Payload);
	/*
	UFUNCTION()
	void OnMontageStart_OverlapActivatie(UAnimMontage* AnimMontage);
	UFUNCTION()
	void OnMontageEnd_OverlapDeActivate(UAnimMontage* AnimMontage, bool Interupted);
	*/
	FHitCheckDelegate HitDelegate;
	
	UFUNCTION()
	void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void SetMontageCycle(UAnimInstance* AnimInstance,UAnimMontage* AnimMontage);
	//애니메이션 실행, 애니메이션 실행하는 동안 적 추적 (Multi로 범위 내의 적을 찾은 뒤, [0] 을 선택하면 Single, 다 선택하면 Multi
	//Effect 적용 시키기.
	UFUNCTION()
	void InitHitAmount();
	
	UPROPERTY(EditAnywhere)
	FGameplayTag StartUpTag;
	
	
};

