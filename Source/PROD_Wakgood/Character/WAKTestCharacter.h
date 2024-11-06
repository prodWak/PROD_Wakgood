// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "WAKDataTable.h"
#include "Input/WAKInputConfig.h"
#include "Components/SphereComponent.h"
#include "Interface/CombatInterface.h"
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
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChange,float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNextAttackCheck, bool);
DECLARE_MULTICAST_DELEGATE(FOnNotifyEnd);



UCLASS(config=Game)
class AWAKTestCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere,Category= "Animation");
	UAnimMontage* NormalAttackAnim; // Player로
	
	
public:
	AWAKTestCharacter();

	FOnNotifyEnd* NotifyEnd; 
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value); //Enemy로

			

protected:
	
	// To add mapping context
	virtual void BeginPlay();



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
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	UWAKAttributeSet* GetAttributeSet() const {return AttributeSet;}
	void SetWeaponOverlap(bool CanOverlap);

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Weapon;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* WeaponCollision;

	UFUNCTION()
	void HealthCheck();
	
	UFUNCTION()
	void HitReactTagChange(const FGameplayTag CallbackTag, int32 NewCount);
	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting = false;
	UPROPERTY(BlueprintReadOnly, Category="Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere)
	UAnimMontage* ReactMontage;
	UFUNCTION()
	UAnimMontage* GetReactMontage();

	void Die() override;
	//멀티로 만들고 싶다면 virtual void MulticastHandleDeath() 함수 구현 필요.

	FOnNextAttackCheck* OnNextAttackCheck;
private:
	UFUNCTION(CallInEditor)
	void SetNormalMode();
	UFUNCTION(CallInEditor)
	void NormalAttack();
	UFUNCTION(CallInEditor)
	void NormalCatch();
	void AsyncLoadWeapon(TSoftObjectPtr<UStaticMesh> WeaponData);
	UFUNCTION(CallInEditor)
	void Experinment_HadokenAbility();
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UDataTable* WeaponMeshDataTable;


	UPROPERTY(EditAnywhere)
	TArray<FGameplayTag> AttackAbilityList;


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
		const FHitResult & SweepResult
		);

	FOnHealthChange HealthChangeDelegate;
protected:
	UPROPERTY(VisibleAnywhere, Category="GAS")
	TObjectPtr<UAbilitySystemComponent> ASC;
	UPROPERTY()
	TObjectPtr<UWAKAttributeSet> AttributeSet;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect ,float Level);
	virtual void InitializeAttributeToEffect();
	void ApplyEffectToTarget(AActor* OtherActor, TSubclassOf<UGameplayEffect> EffectClass);

	UDataTable* CharacterStatusDT;
	FCharacterStatus* NormalCharacterStatus;


	
	
};

