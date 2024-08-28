// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalActor.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h" // OpenLevel �Լ� ���

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

	// ������ ���� Ȥ�� ���� �� �Լ� ���ε�
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APortalActor::BeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APortalActor::EndOverlap);
	
}

void APortalActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
		Character->SetOverlapPortal(this);
	}
}

void APortalActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// ����� �ڵ� ����******************
	/*if (GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(21, 10, FColor::Red, "End!!" + OtherActor->GetName());
	}*/
	// ***********����� �ڵ� ��

	// ���� �������� ���� ������Ʈ�� PlayerCharacter�� ��, ���� MyCharacter�� �浿���� ��Ż ������ �ʱ�ȭ
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (Character != nullptr)
		Character->SetOverlapPortal(nullptr);
}

void APortalActor::Entry()
{
	// �ش� TEXT �̸��� ������ ����.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("L_1-2Stage"));
}

// Called every frame
void APortalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

