// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystem/Abilities/WakGA_AttackBase.h"
#include "Character/WAKTestCharacter.h"
#include "WakGA_NormalAttack1.generated.h"
class UAbilityTask_PlayMontageAndWait;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakGA_NormalAttack1 : public UWakGA_AttackBase
{
	GENERATED_BODY()
public:
	UWakGA_NormalAttack1();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UFUNCTION()
	void NextAttack();
	UFUNCTION()
	void NextAttackCheckDelegate(bool AbleNextAttack);
	UFUNCTION()
	void OnMontageEnded(); 
	

private:
	UPROPERTY(EditAnywhere,Category= "Animation");
	UAnimMontage* NormalAttackAnim;
	UPROPERTY(EditAnywhere,Category= "Animation");
	UAnimMontage* NormalComboAttackAnim;

	UAbilityTask_WaitGameplayEvent* WaitingHitEvent;
	
	FOnNextAttackCheck OnNextAttackCheck;

	UAnimInstance* AnimInstance;

	UPROPERTY()
	bool isAbleNextAttack = false;
	
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	UFUNCTION()
	void ApplyDamageBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> NormalAttackEffect;

	UPROPERTY(EditAnywhere)
	float LaunchForce = 300.f;
	int8 CurrentHitAmount = 0;
	int8 MaxHitAmount = 1;
	AWAKTestCharacter* Avatar;

	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait;

	FTimerHandle* KnockBackTimer;

	UFUNCTION()
	void KnokBack(AWakEnemyCharacter* Enemy,  FVector TargetLocation);

	UPROPERTY(EditAnywhere)
	float InterpSpeed;

	UPROPERTY(VisibleAnywhere)
	TMap<AWakEnemyCharacter*,int> HitEnemies; 
};
