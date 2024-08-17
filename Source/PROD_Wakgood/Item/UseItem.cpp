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
        // ĳ������ �κ��丮�� �������� �߰�
        Character->AddItemToInventory(this);

        // �������� ��Ȱ��ȭ�ϰų� ����
        this->SetActorEnableCollision(false);
        this->SetActorHiddenInGame(true);

        // �ʿ�� �������� ���� ���¸� �����ϱ� ���� �߰� �۾� ����
        // ��: �κ��丮 UI ������Ʈ, �α� ��� ��
    }
}

AUseItem::AUseItem()
{

}

AUseItem::~AUseItem()
{

}