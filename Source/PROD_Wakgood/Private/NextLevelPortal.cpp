// Fill out your copyright notice in the Description page of Project Settings.

//
//#include "NextLevelPortal.h"
//
//void ANextLevelPortal::BeginPlay()
//{
//	Super::BeginPlay();
//	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ANextLevelPortal::BeginOverlap);
//	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ANextLevelPortal::EndOverlap);
//}
//
//void ANextLevelPortal::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (GEngine != nullptr)
//	{
//		GEngine->AddOnScreenDebugMessage(1, 10, FColor::Blue, OtherActor->GetName());
//	}
//}
//
//void ANextLevelPortal::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (GEngine != nullptr)
//	{
//		GEngine->AddOnScreenDebugMessage(2, 10, FColor::Red, "End!!" + OtherActor->GetName());
//	}
//}
//
//ANextLevelPortal::ANextLevelPortal()
//{
//	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
//	SphereComponent->SetupAttachment(GetRootComponent());
//}
