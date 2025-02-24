#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/WakInteractionInterface.h"

#include "WakCharacterBase.generated.h"

class UAbilitySystemComponent;
class UWakHealthComponent;

UCLASS()
class PROD_WAKGOOD_API AWakCharacterBase : public ACharacter, public IAbilitySystemInterface, public IInteractionInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWakHealthComponent> HealthComponent;

public:
	AWakCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/*
	 * AbilitySystem
	 */
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wak|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnDeathStarted(AActor* OwningActor);

	// Ends the death sequence for the character (detaches controller, destroys pawn, etc...)
	UFUNCTION()
	virtual void OnDeathFinished(AActor* OwningActor);

	void DisableMovementAndCollision();
	void DestroyDueToDeath();
	void UninitAndDestroy();

	// Called when the death sequence for the character has completed
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDeathFinished"))
	void K2_OnDeathFinished();
};
