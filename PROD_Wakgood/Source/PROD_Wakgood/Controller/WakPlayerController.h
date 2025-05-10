// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WakGameplayTags.h"
#include "GenericTeamAgentInterface.h"
#include "WakPlayerController.generated.h"

class UWakInputConfig;
class UWakAbilitySystemComponent;
class UInputAction;

struct FInputActionValue;
struct FInputActionInstance;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	/*
	 * 일반 커맨드
	   (빠르게) A + A / D + D: 달리기
		K → K(hold) / (떨어질 때) K(hold): 공중에서 왁초리를 빙글빙글 돌리며 호버링
				: K(hold) 상태에서 W,A,S,D로 공중에서 이동, 바닥에 닿으면 호버링 종료
		K + J: 점프 후 공중 공격
		(특수몹에게) J + S: 특수몹 포획 후 흡수 변신
		(특수몹에게) J + J: 특수몹 포획 후 던지기

		## 변신 폼 마다 스킬이 다름 => 스테이트 구분해서 태그 부여
	 */
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wak|Data", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWakInputConfig> InputConfigDataAsset;

	UPROPERTY()
	TObjectPtr<UWakAbilitySystemComponent> WakAbilitySystemComponent;

	UPROPERTY()
	bool bIsInteractInput = false;

	UPROPERTY()
	FGenericTeamId PlayerTeamId;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
		
	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);
	void GamePause(const FInputActionValue& Value);
	void OnInteract();

	void AbilityInputPressed(FGameplayTag InInputTag);
	void AbilityInputReleased(FGameplayTag InInputTag);

	const FInputActionInstance* GetInputActionInstance(const UInputAction* InInputAction) const;
	float GetElapsedSeconds(const UInputAction* InInputAction) const;

	UFUNCTION(BlueprintPure, Category = "Wak|Input")
	bool IsAbsorptionAction(const UInputAction* InInputAction, const float AbsorbHoldTime) const;
	
public:
	AWakPlayerController();
	
	virtual FGenericTeamId GetGenericTeamId() const override;
	
	void SwitchInteractInput();
	bool GetIsInteractInput() const;
};