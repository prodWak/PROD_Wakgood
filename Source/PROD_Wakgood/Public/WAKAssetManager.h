// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "WAKAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API UWAKAssetManager : public UAssetManager
{
	GENERATED_BODY()
	static UWAKAssetManager& Get();
	virtual void StartInitialLoading() override;
	
};
