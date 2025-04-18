#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/WakInteractionInterface.h"

#include "WakCharacterBase.generated.h"

class UWakAbilitySystemComponent;
class UWakAttributeSet;
class UAbilitySystemComponent;
class UWakHealthComponent;
class UWakStartUpDataBase;

UCLASS()
class PROD_WAKGOOD_API AWakCharacterBase : public ACharacter, public IAbilitySystemInterface, public IInteractionInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWakHealthComponent> HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wak|Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWakAbilitySystemComponent> WakAbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wak|Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWakAttributeSet> WakAttribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wak|CharacterData", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWakStartUpDataBase> CharacterStartUpData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wak|CharacterWeapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Weapon;

public:
	AWakCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	
	UFUNCTION()
	virtual void OnDeathStarted(AActor* OwningActor);

	// Ends the death sequence for the character (detaches controller, destroys pawn, etc...)
	UFUNCTION()
	virtual void OnDeathFinished(AActor* OwningActor);

	void DisableMovementAndCollision() const;
	void DestroyDueToDeath();
	void UnInitAndDestroy();

	// Called when the death sequence for the character has completed
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDeathFinished"))
	void K2_OnDeathFinished();

	FORCEINLINE TSoftObjectPtr<UWakStartUpDataBase> GetWakStartUpData() const { return CharacterStartUpData; }
	
public:
	FORCEINLINE UWakAbilitySystemComponent* GetWakAbilitySystemComponent() const { return WakAbilitySystemComponent; }
	FORCEINLINE UWakAttributeSet* GetWakAttribute() const { return WakAttribute; }
};
