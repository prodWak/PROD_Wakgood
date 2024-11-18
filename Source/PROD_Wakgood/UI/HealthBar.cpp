// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"

#include "AbilitySystem/WAKASC.h"
#include "AbilitySystem/WAKAttributeSet.h"

void UHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
	PlayerCharacter = Cast<AWakPlayerCharacter>(GetOwningPlayerPawn());
	PlayerAbilitySystemComponent = Cast<UWAKASC>(PlayerCharacter->GetAbilitySystemComponent());
	PlayerAttributeSet = PlayerCharacter->GetAttributeSet();
	HealthProgressBar->SetPercent(1.0f);
	PlayerAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetHealthAttribute()).AddUObject(this,&UHealthBar::OnCurrentHealtChange);
	PlayerAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetMaxHealthAttribute()).AddUObject(this,&UHealthBar::OnMaxHealtChange);
}


void UHealthBar::OnCurrentHealtChange(const FOnAttributeChangeData& ChangedAttribute)
{
	if(ChangedAttribute.Attribute == PlayerAttributeSet->GetHealthAttribute())
	{
		HealthProgressBar->SetPercent(PlayerAttributeSet->GetHealth()/PlayerAttributeSet->GetMaxHealth());
	}
}

void UHealthBar::OnMaxHealtChange(const FOnAttributeChangeData& ChangedAttribute)
{
	if(ChangedAttribute.Attribute == PlayerAttributeSet->GetMaxHealthAttribute())
	{
		HealthProgressBar->SetPercent(PlayerAttributeSet->GetHealth()/PlayerAttributeSet->GetMaxHealth());
	}
}



