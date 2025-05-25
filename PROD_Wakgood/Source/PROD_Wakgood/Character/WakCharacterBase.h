#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/WakInteractionInterface.h"
#include "Interfaces/WakPawnCombatInterface.h"

#include "WakCharacterBase.generated.h"

class UWakAbilitySystemComponent;
class UWakAttributeSet;
class UAbilitySystemComponent;
class UWakStartUpDataAssetBase;

UCLASS()
class PROD_WAKGOOD_API AWakCharacterBase : public ACharacter, public IAbilitySystemInterface, public IInteractionInterface, public IWakPawnCombatInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wak|Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWakAbilitySystemComponent> WakAbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wak|Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWakAttributeSet> WakAttribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wak|CharacterData", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWakStartUpDataAssetBase> CharacterStartUpData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wak|CharacterWeapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Weapon;

public:
	AWakCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UWakPawnCombatComponent* GetWakPawnCombatComponent() override;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	FORCEINLINE TSoftObjectPtr<UWakStartUpDataAssetBase> GetWakStartUpData() const { return CharacterStartUpData; }
	
public:
	FORCEINLINE UWakAbilitySystemComponent* GetWakAbilitySystemComponent() const { return WakAbilitySystemComponent; }
	FORCEINLINE UWakAttributeSet* GetWakAttribute() const { return WakAttribute; }
};
