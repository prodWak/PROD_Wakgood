// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "WakAbilityTypes.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Game/WAKTestGameMode.h"
#include "Kismet/GameplayStatics.h"

void UWakAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContext, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AWAKTestGameMode* GameMode = Cast<AWAKTestGameMode>(UGameplayStatics::GetGameMode(WorldContext));
	if(GameMode == nullptr)
	{
		return;
	}
	AActor* AvatarActor = ASC->GetAvatarActor();
	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(AvatarActor);
	FCharacterClassDefaultInfo ClassDefaultInfo = GameMode->CharacterClassInfo->GetClassInfo(CharacterClass);
	
	const FGameplayEffectSpecHandle EffectSpec = ASC->MakeOutgoingSpec(ClassDefaultInfo.Attributes,Level,EffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get()); // 기본 속성 초기화용.
	//const UGameplayEffect *GameplayEffect, float Level, const FGameplayEffectContextHandle& EffectContext, FPredictionKey PredictionKey = FPredictionKey()
}

bool UWakAbilitySystemLibrary::IsBlockHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FWakGameplayEffectContext* WakEffectContext = static_cast<const FWakGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return WakEffectContext->IsBlockedHit();
	}
	return false;
	
}

bool UWakAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const FWakGameplayEffectContext* WakEffectContext = static_cast<const FWakGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return WakEffectContext->IsCriticalHit();
	}
	return false;
}

void UWakAbilitySystemLibrary::SetIsBlockHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsBlockHit)
{
	/*if(FWakGameplayEffectContext* WakEffectContext = Cast<FWakGameplayEffectContext>(EffectContextHandle.Get()))
	{  
		return WakEffectContext->SetIsBlockedHit(bInIsBlockHit);
	}*/

}

void UWakAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsCriticalHit)
{
	/*
	if(FWakGameplayEffectContext* WakEffectContext = Cast<FWakGameplayEffectContext>(EffectContextHandle.Get()))
	{
		return WakEffectContext->SetIsBlockedHit(bInIsCriticalHit);
	}
*/
}
