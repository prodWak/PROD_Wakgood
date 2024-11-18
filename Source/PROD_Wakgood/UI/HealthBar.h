// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/WakPlayerCharacter.h"
#include "Components/ProgressBar.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;

public:
	
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AWakPlayerCharacter> PlayerCharacter;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UWAKASC> PlayerAbilitySystemComponent;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UWAKAttributeSet> PlayerAttributeSet;

	void OnCurrentHealtChange(const FOnAttributeChangeData& ChangedAttribute);
	void OnMaxHealtChange(const FOnAttributeChangeData& ChangedAttribute);
	

	
	
};
