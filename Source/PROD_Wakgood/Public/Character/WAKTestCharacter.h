// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "WAKInputConfig.h"
#include "WAKTestCharacter.generated.h"

class UWAKAttributeSet;
class UWAKASC;
class UAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UDataTable;
struct FInputActionValue;


UCLASS(config=Game)
class AWAKTestCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AWAKTestCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	void ApplyEffectToTarget(AActor* OtherActor, TSubclassOf<UGameplayEffect> EffectClass);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> PrimaryEffect;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DamageEffect;
	//void AbilityActivateByTag();
	void ChangeWeaponByTag();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	UWAKAttributeSet* GetAttributeSet() const {return AttributeSet;}
	void SetWeaponOverlap(bool CanOverlap);
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWAKASC> ASC;
	TObjectPtr<UWAKAttributeSet> AttributeSet;
	
	virtual void PossessedBy(AController* NewController) override;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect ,float Level);
	void InitializeAttributeToEffect();
	void AsyncLoadWeapon(TSoftObjectPtr<UStaticMesh> WeaponData);

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Weapon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UDataTable* WeaponMeshDataTable;

	UPROPERTY(EditAnywhere)
	TArray<FGameplayTag> AttackAbilityList;

	void AbilityInputTagPressed(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UWAKInputConfig> InputConfig;

	FGameplayTag CharacterType;
	
		UFUNCTION()
	void OnWeaponBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult);
};

