// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/Abilities/WakGA_AttackBase.h"
#include "WakGA_NormalCatch.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWakGA_NormalCatch : public UWakGA_AttackBase
{
	GENERATED_BODY()
	UWakGA_NormalCatch();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> CatchAnimMontage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> CatchEffect;	
	TObjectPtr<AWAKTestCharacter> Avatar;
	TObjectPtr<AWakEnemyCharacter> Enemy;

	UPROPERTY(EditAnywhere)
	float InterpSpeed = 10.f;

	UFUNCTION()
	void ApplyEffectToTarget();

	UFUNCTION()
	void GrabEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


	
};
