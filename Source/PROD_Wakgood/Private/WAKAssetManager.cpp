// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\WAKAssetManager.h"

#include "..\Public\WAKTag.h"
UWAKAssetManager& UWAKAssetManager::Get()
{
	check(GEngine);
	UWAKAssetManager* WAKAssetManager = Cast<UWAKAssetManager>(GEngine->AssetManager);
	return *WAKAssetManager;
}

void UWAKAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FWAKGameplayTags::InitializeNativeGameplayTags();
}
