// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformActor.h"

#include "Character/WakPlayerCharacter.h"


// Sets default values
APlatformActor::APlatformActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	SetRootComponent(PlatformMesh);
	UpperPlayerDetectBox = CreateDefaultSubobject<UBoxComponent>(TEXT("UpperPlayerDetectBox"));
	UpperPlayerDetectBox->SetupAttachment(RootComponent);
	
	UnderPlayerDetectBox = CreateDefaultSubobject<UBoxComponent>(TEXT("UnderPlayerDetectBox"));
	UnderPlayerDetectBox->SetupAttachment(RootComponent);
	
	UpperPlayerDetectBox->OnComponentBeginOverlap.AddUniqueDynamic(this,&APlatformActor::BeginOverlapUpper);
	UpperPlayerDetectBox->OnComponentEndOverlap.AddUniqueDynamic(this,&APlatformActor::EndOverlapUpper);

	UnderPlayerDetectBox->OnComponentBeginOverlap.AddUniqueDynamic(this,&APlatformActor::BeginOverlapUnder);
	UnderPlayerDetectBox->OnComponentEndOverlap.AddUniqueDynamic(this,&APlatformActor::EndOverlapUnder);
}

// Called when the game starts or when spawned
void APlatformActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformActor::BeginOverlapUnder(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AWakPlayerCharacter* Player = Cast<AWakPlayerCharacter>(OtherActor))
	{
		if(Player->GetActorLocation().Z <= GetActorLocation().Z)
		{
			UE_LOG(LogTemp,Warning,TEXT("Overlap"));
			//Player->SetPlatformCollisionResponseBlock();
			PlatformMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
		}
	}
}

void APlatformActor::EndOverlapUnder(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(AWakPlayerCharacter* Player = Cast<AWakPlayerCharacter>(OtherActor))
	{
		if(Player->GetActorLocation().Z > GetActorLocation().Z)
		{
			UE_LOG(LogTemp,Warning,TEXT("End Overlap"));
			//Player->SetPlatformCollisionResponseBlock();
			PlatformMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Block);
		}
	}
}

void APlatformActor::BeginOverlapUpper(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AWakPlayerCharacter* Player = Cast<AWakPlayerCharacter>(OtherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("Overlap"));
		//Player->SetPlatformCollisionResponseBlock();
		PlayerCharacter = Player;
		PlayerCharacter->bAbleDown = true;
		PlayerCharacter->OnMoveUnderPlatform.AddLambda([this]()
		{
			PlatformMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
		});
	}
}

void APlatformActor::EndOverlapUpper(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(AWakPlayerCharacter* Player = Cast<AWakPlayerCharacter>(OtherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("Overlap"));
		//Player->SetPlatformCollisionResponseBlock();
		//PlatformMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Block);
		Player->bAbleDown = false;
		Player->OnMoveUnderPlatform.RemoveAll(this);
	}
}

// Called every frame
void APlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

