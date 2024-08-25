// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BoxComponent.h"
#include "PROD_Wakgood/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PROD_Wakgood/Interaction/WakItemBase.h"



void AWakItemBase::BeginPlay()
{
	Super::BeginPlay();
}

AWakItemBase::AWakItemBase()
{
    PrimaryActorTick.bCanEverTick = true;
}


void AWakItemBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ATP_ThirdPersonCharacter* Character = Cast<ATP_ThirdPersonCharacter>(OtherActor);
    if (Character)
    {
        Character->SetOverlapItem(this);
    }
}

void AWakItemBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ATP_ThirdPersonCharacter* Character = Cast<ATP_ThirdPersonCharacter>(OtherActor);
    if (Character)
    {
        Character->SetOverlapItem(nullptr);
    }
}

void AWakItemBase::Interaction(AActor* target)
{
    ATP_ThirdPersonCharacter* Character = Cast<ATP_ThirdPersonCharacter>(target);
    if (Character)
    {
        Character->AddItemToInventory(this);

        // 아이템을 비활성화하거나 제거
        this->SetActorEnableCollision(false);
        this->SetActorHiddenInGame(true);
    }
}