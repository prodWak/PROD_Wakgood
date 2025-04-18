// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WakWeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class PROD_WAKGOOD_API AWakWeaponBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> WeaponMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wak|Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> WeaponCollisionComponent;
	
public:	
	AWakWeaponBase();


	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() const { return WeaponMeshComponent; }
	FORCEINLINE UBoxComponent* GetWeaponCollisionComponent() const { return WeaponCollisionComponent; }

};
