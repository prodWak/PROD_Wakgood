// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem\WAKAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "WAKTag.h"
#include "Character/WAKTestCharacter.h"

UWAKAttributeSet::UWAKAttributeSet()
{
	const FWAKGameplayTags& GameplayTags = FWAKGameplayTags::Get();

}
void UWAKAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	
	Super::PostGameplayEffectExecute(Data);
	
	
	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0,GetMaxHealth()));
	}
	if(Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f); // IncomingDamage는 0으로 초기화
		if(LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth,0,GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.f; // 죽음에 이르는 피해를 받음.
			if(bFatal)
			{
				if(ICombatInterface* TargetActor = Cast<ICombatInterface>(Data.Target.GetAvatarActor()))
				{
					TargetActor->Die();
					UE_LOG(LogTemp,Warning,TEXT("Die"));
				}
			}
		}
	}
}

void UWAKAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if(Attribute == GetHealthAttribute())
	{
		float OldHealth = GetHealth();
		if(OldHealth > NewValue)
		{
			AActor* SourceActor = GetOwningActor();
			SourceActor->FindComponentByClass<UAbilitySystemComponent>()->AddLooseGameplayTag(FWAKGameplayTags::Get().Effects_HitReact);
		}
		NewValue = FMath::Clamp(NewValue,0, GetMaxHealth());
	}
}
