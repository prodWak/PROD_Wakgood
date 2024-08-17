// Fill out your copyright notice in the Description page of Project Settings.


#include "UseItem.h"
#include "PROD_Wakgood/Character/MyCharacter.h"
#include "Components/SphereComponent.h"



void AUseItem::BeginPlay()
{
    Super::BeginPlay();
}

void AUseItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
    if (Character)
    {
        Character->SetOverlapItem(this);
    }
}

void AUseItem::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
    if (Character)
    {
        Character->SetOverlapItem(nullptr);
    }
}


void AUseItem::Pickup(AMyCharacter* Character)
{
    if (Character)
    {
        // 캐릭터의 인벤토리에 아이템을 추가
        Character->AddItemToInventory(this);

        // 아이템을 비활성화하거나 제거
        this->SetActorEnableCollision(false);
        this->SetActorHiddenInGame(true);

        // 필요시 아이템의 논리적 상태를 관리하기 위해 추가 작업 수행
        // 예: 인벤토리 UI 업데이트, 로그 기록 등
    }
}

AUseItem::AUseItem()
{

}

AUseItem::~AUseItem()
{

}