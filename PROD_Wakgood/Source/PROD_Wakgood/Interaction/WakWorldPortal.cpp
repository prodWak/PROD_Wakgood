// Fill out your copyright notice in the Description page of Project Settings.

#include "WakWorldPortal.h"

#include "Character/WakCharacterBase.h"
#include "Components/WidgetComponent.h"

#include "PROD_Wakgood/Game/WakMainGameInstance.h"
#include "Kismet/GameplayStatics.h"

AWorldPortal::AWorldPortal()
{	
	LocationName = TEXT("World1");
	PlayerLastLocationIndex = 1;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize(FVector2D(300, 100));
}

void AWorldPortal::Interaction(AActor* target)
{
	Super::Interaction(target);
	UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetWorld()->GetGameInstance());   
	if (GameInstance)
	{
		UGameplayStatics::OpenLevel(this, LocationName, false);		
		GameInstance->SetPlayerLastLocation(PlayerLastLocationIndex);
		UE_LOG(LogTemp, Warning, TEXT("Set Player Last Location : %d"), PlayerLastLocationIndex);
	}
}

void AWorldPortal::BeginPlay()
{
	Super::BeginPlay();
	WidgetComponent->SetVisibility(false);
}

void AWorldPortal::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AWakCharacterBase* OverlappingCharacter = Cast<AWakCharacterBase>(OtherActor);
		if(OverlappingCharacter && GetWorld())
		{
			WidgetComponent->SetVisibility(true);
		}
	}
}

void AWorldPortal::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	WidgetComponent->SetVisibility(false);
}
