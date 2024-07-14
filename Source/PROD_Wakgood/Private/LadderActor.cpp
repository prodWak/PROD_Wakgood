// Fill out your copyright notice in the Description page of Project Settings.


#include "LadderActor.h"
#include "MyCharacter.h"

// Sets default values
ALadderActor::ALadderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(MeshComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ALadderActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALadderActor::BeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ALadderActor::EndOverlap);
	
}

void ALadderActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ����� �ڵ� ����******************
	//if (GEngine != nullptr)
	//{
	//	GEngine->AddOnScreenDebugMessage(20, 10, FColor::Blue, OtherActor->GetName());
	//}
	// ***********����� �ڵ� ��

	// ���� �浹 �� ������Ʈ�� PlayerCharacter�� ��, ���� �浹���� ��Ż ���� �Ѱ���
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (Character != nullptr)
	{
		Character->SetOverlapLadder(this);
		Character->SetLadderStartState();
	}
}

void ALadderActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// ����� �ڵ� ����******************
	//if (GEngine != nullptr)
	//{
	//	GEngine->AddOnScreenDebugMessage(21, 10, FColor::Red, "End!!" + OtherActor->GetName());
	//}
	// ***********����� �ڵ� ��

	// ���� �������� ���� ������Ʈ�� PlayerCharacter�� ��, ���� MyCharacter�� �浿���� ��Ż ������ �ʱ�ȭ
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (Character != nullptr)
	{
		Character->SetOverlapLadder(nullptr);
		Character->SetLadderEndState();
	}
}

// Called every frame
void ALadderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

