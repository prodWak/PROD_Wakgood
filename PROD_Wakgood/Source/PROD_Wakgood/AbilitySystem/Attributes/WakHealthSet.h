#pragma once

#include "AbilitySystemComponent.h"
#include "WakAttributeSet.h"
#include "NativeGameplayTags.h"
#include "WakHealthSet.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_Damage);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageImmunity);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageSelfDestruct);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_FellOutOfWorld);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Wak_Damage_Message);

struct FGameplayEffectModCallbackData;

UCLASS(BlueprintType)
class UWakHealthSet : public UWakAttributeSet
{
	GENERATED_BODY()

public:	
	UWakHealthSet();

	ATTRIBUTE_ACCESSORS(UWakHealthSet, Health);
	ATTRIBUTE_ACCESSORS(UWakHealthSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UWakHealthSet, Healing);
	ATTRIBUTE_ACCESSORS(UWakHealthSet, Damage);

	mutable FWakAttributeEvent OnHealthChanged;
	mutable FWakAttributeEvent OnMaxHealthChanged;
	mutable FWakAttributeEvent OnOutOfHealth;

protected:
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:

	UPROPERTY(BlueprintReadOnly, Category = "Wak|Health", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Wak|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	bool bOutOfHealth;

	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;

	// -------------------------------------------------------------------
	//	Meta Attribute (please keep attributes that aren't 'stateful' below 
	// -------------------------------------------------------------------

	// Incoming healing. This is mapped directly to +Health
	UPROPERTY(BlueprintReadOnly, Category = "Wak|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Healing;

	// Incoming damage. This is mapped directly to -Health
	UPROPERTY(BlueprintReadOnly, Category = "Wak|Health", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Damage;
};
