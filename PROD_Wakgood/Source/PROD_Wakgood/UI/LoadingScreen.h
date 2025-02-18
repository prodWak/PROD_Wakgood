// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine.h
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
// Generated
#include "LoadingScreen.generated.h"

UCLASS()
class PROD_WAKGOOD_API ALoadingScreen : public AHUD
{
	GENERATED_BODY()
	
public:
	ALoadingScreen();

protected:
	virtual void BeginPlay() override;

public:
	void RemoveLoadingScreen();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "MenuUI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LoadingScreenClass;
	
	UPROPERTY()
	UUserWidget* LoadingScreenWidget;
};
