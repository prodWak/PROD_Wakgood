// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WakCharacterBase.h"
#include "WakWakGoodCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWakPlayerCombatComponent;
class AWakPlayerController;

/*
 * 처음에 부여한 시작 어빌리티는 변경이 가늗한가? => StartUpDataAsset에서 부여한 어빌리티
 *		ㄴ 흡수한 적의 태그를 보관하고 변신 할 때 태그를 검사해서 맵에서 태그(key)를 찾고 일치한다면
 *		   DataAsset(item)에서 메시랑 머 이것저것 변경해야 하나?
 *
 *	
 */

UCLASS()
class PROD_WAKGOOD_API AWakWakGoodCharacter : public AWakCharacterBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWakPlayerCombatComponent> WakPlayerCombatComponent;

public:
	AWakWakGoodCharacter();
	virtual UWakPawnCombatComponent* GetWakPawnCombatComponent() override;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return SpringArmComponent; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCameraComponent; }
	FORCEINLINE UWakPlayerCombatComponent* GetWakPlayerCombatComponent() const { return WakPlayerCombatComponent; }
};
