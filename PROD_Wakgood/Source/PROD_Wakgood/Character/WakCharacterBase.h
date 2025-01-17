#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/WakInteractionInterface.h"

#include "WakCharacterBase.generated.h"

class UAbilitySystemComponent;
class UWakHealthComponent;

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputComponent;
class UInputAction;
struct FInputActionValue;

class UBoxComponent;

class AInteractionBase;

UCLASS()
class PROD_WAKGOOD_API AWakCharacterBase : public ACharacter, public IAbilitySystemInterface, public IInteractionInterface
{
	GENERATED_BODY()

	/*
	 * Component
	 */

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWakHealthComponent> HealthComponent;
	
	/*
	 * Input
	 */
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wak|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wak|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wak|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/*
	 * Interaction
	 */
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wak|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wak|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> InteractionBox;

	IInteractionInterface* Interface = nullptr;

public:
	void SwitchInteractInput();
	bool GetIsInteractInput() const;

	AWakCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

	// Move
	void Move(const FInputActionValue& Value);
	
	/*
	 * For Interaction
	 */
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	AInteractionBase* InteractionTarget;
	
	void OnInteract();
	bool bIsInteractInput = false;

public:
	// Get
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
