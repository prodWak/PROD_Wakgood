#pragma once
#include "GameplayEffectTypes.h"
#include "WakAbilityTypes.generated.h"

USTRUCT()
struct FWakGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
public:

	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsBlockedHit() const { return bIsBlockedHit; }
	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	
	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}

	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);

	virtual FWakGameplayEffectContext* Duplicate() const
	{
		FWakGameplayEffectContext* NewContext = new FWakGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

protected:
	UPROPERTY()
	bool bIsBlockedHit = false;
	UPROPERTY()
	bool bIsCriticalHit = false;

	
	
};

template<>
struct TStructOpsTypeTraits<FWakGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FWakGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
	
};