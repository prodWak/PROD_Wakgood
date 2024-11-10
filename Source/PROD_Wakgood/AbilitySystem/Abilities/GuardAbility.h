// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WAKGA.h"
#include "Components/BoxComponent.h"
#include "GuardAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UGuardAbility : public UWAKGA
{
	GENERATED_BODY()
	UGuardAbility();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> GuardEffectClass;

	UFUNCTION()
	void OnRemoveBlockingTag(const FGameplayTag CallbackTag,int32 NewCount);

	FDelegateHandle BlockTagDelegateHandle;

	UBoxComponent* PlayerShiled;
	
	UFUNCTION()
	void ShiledOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
