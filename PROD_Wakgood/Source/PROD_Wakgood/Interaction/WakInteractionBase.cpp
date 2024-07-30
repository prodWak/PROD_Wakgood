// Fill out your copyright notice in the Description page of Project Settings.


#include "WakInteractionBase.h"
#include "PROD_Wakgood/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

// Sets default values
AWakInteractionBase::AWakInteractionBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = _RootComponent;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionProfileName(TEXT("OverlapAll"));

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
}

void AWakInteractionBase::BeginPlay()
{
	Super::BeginPlay();
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AWakInteractionBase::OnBeginOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AWakInteractionBase::OnEndOverlap);

	PointLight->SetIntensity(0);
}

void AWakInteractionBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ATP_ThirdPersonCharacter* OverlappingCharacter = Cast<ATP_ThirdPersonCharacter>(OtherActor);
		if(OverlappingCharacter && GetWorld())
		{
			PointLight->SetIntensity(10000);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, FString::Printf(TEXT("The Actor Could not be casted to a character")));
		}
	}
}

void AWakInteractionBase::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PointLight->SetIntensity(0);
}

void AWakInteractionBase::Interaction(AActor* target)
{
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Call Interaction")));
}