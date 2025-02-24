// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WakPlayerController.generated.h"

class AWakWakGoodCharacter;

class UInputMappingContext;
class UInputAction;
class AInteractionBase;
class IInteractionInterface;

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakPlayerController : public APlayerController
{
	GENERATED_BODY()
	
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
	
protected:
	/*
	 * Input Variable
	 */
	
	UPROPERTY(EditDefaultsOnly, Category = "Wak|Input")
	TObjectPtr<UInputMappingContext> IMC_Default;

	// 이동 : W, A, S, D
	UPROPERTY(EditDefaultsOnly, Category = "Wak|Input")
	TObjectPtr<UInputAction> IA_Move;

	// 점프 : K
	UPROPERTY(EditDefaultsOnly, Category = "Wak|Input")
	TObjectPtr<UInputAction> IA_Jump;

	// 일시정지 및 메뉴 열기 : ESC
	UPROPERTY(EditDefaultsOnly, Category = "Wak|Input")
	TObjectPtr<UInputAction> IA_Pause;

	// 상호작용 : E
	UPROPERTY(EditAnywhere, Category = "Wak|Input")
	TObjectPtr<UInputAction> IA_Interaction;
	
	// 이하 DataConfig으로 관리 예정
	// 기본 공격 : J, 홀드 시 포획
	UPROPERTY(EditDefaultsOnly, Category = "Wak|Input")
	TObjectPtr<UInputAction> IA_Attack;

	// 특수 커맨드 : L, 특정 스킬 사용 시
	UPROPERTY(EditDefaultsOnly, Category = "Wak|Input")
	TObjectPtr<UInputAction> IA_SpecialCommand;

	// 변신 풀기 : M
	UPROPERTY(EditDefaultsOnly, Category = "Wak|Input")
	TObjectPtr<UInputAction> IA_Untransformed;

	// 달리기 : Left Shift, 홀드와 트리거 선택 가능
	UPROPERTY(EditDefaultsOnly, Category = "Wak|Input")
	TObjectPtr<UInputAction> IA_Run;

	// 변신 커맨드 : Space Bar
	UPROPERTY(EditDefaultsOnly, Category = "Wak|Input")
	TObjectPtr<UInputAction> IA_TransformCommand;

	// Character
	TObjectPtr<AWakWakGoodCharacter> WakCharacter;
	
	// Interaction
	UPROPERTY()
	AInteractionBase* InteractionTarget = nullptr;
	
	IInteractionInterface* InteractionInterface = nullptr;
	
	bool bIsInteractInput = false;
	
	/*
	 * Function
	 */

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
		
	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);
	void GamePause(const FInputActionValue& Value);
	
	void OnInteract();

public:
	void SwitchInteractInput();
	void SetInteractionTarget(AActor* TargetActor);
	
	bool GetIsInteractInput() const;
};