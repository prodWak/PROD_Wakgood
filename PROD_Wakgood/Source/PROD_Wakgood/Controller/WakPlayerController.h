// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WakPlayerController.generated.h"

class UWakInputConfig;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakPlayerController : public APlayerController
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
	bool bIsInteractInput = false;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
		
	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);
	void GamePause(const FInputActionValue& Value);
	
	void OnInteract();

public:
	void SwitchInteractInput();
	
	bool GetIsInteractInput() const;
};