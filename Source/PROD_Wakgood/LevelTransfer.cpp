#include "LevelTransfer.h"
#include "Components\BoxComponent.h"
#include "Kismet\GameplayStatics.h"

ALevelTransfer::ALevelTransfer()
{
	PrimaryActorTick.bCanEverTick = true;
	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void ALevelTransfer::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if(Pawn != nullptr)
	{
		UGameplayStatics::OpenLevel(this, TransferLevelName, false, TransferGameMode);
	}
}

// Called when the game starts or when spawned
// void ALevelTransfer::BeginPlay()
// {
// 	Super::BeginPlay();
	
// }
