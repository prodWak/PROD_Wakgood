#include "WakAttributeSet.h"
#include "AbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(WakAttributeSet)

class UWorld;

UWakAttributeSet::UWakAttributeSet()
{
}

UWorld* UWakAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UAbilitySystemComponent* UWakAttributeSet::GetAbilitySystemComponent() const
{
	return GetOwningAbilitySystemComponent();
}

