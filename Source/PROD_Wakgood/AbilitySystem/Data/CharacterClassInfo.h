// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Normal,
	Sword,
	Hammer,
	Ninja,
	Ranger,
	Fighter,
	Ice,
	Fire,
	Mic,
	Spark,
	Paper
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category= "Class Default")
	TSubclassOf<UGameplayEffect> Attributes; //Effect에 Tag도 같이. 
};

//각 CharacterClass 별 기본속성으로 사용할 Effect를 만들어서 사용하면 됨.

UCLASS()
class PROD_WAKGOOD_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,Category="Character Class Default")
	//클래스별 개별 데이터 
	TMap<ECharacterClass,FCharacterClassDefaultInfo> CharacterClassInformation;

	//클래스 공용 데이터 (모두가 같은 Value)
	FCharacterClassDefaultInfo GetClassInfo(ECharacterClass CharacterClass);
};


