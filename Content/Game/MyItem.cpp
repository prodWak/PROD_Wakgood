// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/MyItem.h"
#include "Components/SphereComponent.h"
#include "Character/MyCharacter.h"


// Called when the game starts or when spawned
void AMyItem::BeginPlay()
{
    Super::BeginPlay();
}

AMyItem::AMyItem()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->SetupAttachment(Mesh);

    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyItem::BeginOverlap);
    SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AMyItem::EndOverlap);
}

void AMyItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
    if (Character != nullptr)
    {
        //충돌되면 해당 아이템을 set
        Character->SetOverlapItem(this);
    }
}

void AMyItem::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
    if (Character != nullptr)
    {
        //충돌이 끝나면 null값으로 set
        Character->SetOverlapItem(nullptr);
    }
}