#include "WakAttributeSet.h"
#include "GameplayEffectExtension.h"

UWakAttributeSet::UWakAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitAttackPower(1.f);
	InitDamageTaken(1.f);
}

void UWakAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		
		SetCurrentHealth(NewCurrentHealth);
		SetDamageTaken(0.f);
		
		/* TODO : UI 업데이트, Death 컨디션 처리
		if (NewCurrentHealth <= 0.f)
		{
		} */
	}
}