// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalActor.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h" // OpenLevel 함수 사용

APortalActor::APortalActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(MeshComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(GetRootComponent());
}

void APortalActor::BeginPlay()
{
	Super::BeginPlay();

	// 오버랩 시작 혹은 끝날 시 함수 바인딩
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APortalActor::BeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APortalActor::EndOverlap);
	
}

void APortalActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 디버깅 코드 시작******************
	//if (GEngine != nullptr)
	//{
	//	GEngine->AddOnScreenDebugMessage(20, 10, FColor::Blue, OtherActor->GetName());
	//}
	// ***********디버깅 코드 끝

	// 현재 충돌 한 오브젝트가 PlayerCharacter일 때, 현재 충돌중인 포탈 정보 넘겨줌
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (Character != nullptr)
	{
		Character->SetOverlapPortal(this);
	}
}

void APortalActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// 디버깅 코드 시작******************
	/*if (GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(21, 10, FColor::Red, "End!!" + OtherActor->GetName());
	}*/
	// ***********디버깅 코드 끝

	// 현재 오버랩이 끝난 오브젝트가 PlayerCharacter일 때, 현재 MyCharacter의 충동줄인 포탈 데이터 초기화
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (Character != nullptr)
		Character->SetOverlapPortal(nullptr);
}

void APortalActor::Entry()
{
	// 해당 TEXT 이름의 레벨을 연다.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("L_1-2Stage"));
}

// Called every frame
void APortalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

