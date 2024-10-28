// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/WakProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WAKTag.h"
#include "Character/WAKTestCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AWakProjectile::AWakProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	RootComponent = ProjectileMesh;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	CollisionBox->SetupAttachment(RootComponent);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 550.f;
	ProjectileMovementComponent->MaxSpeed = 550.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	//ProjectileMovementComponent->bRotationFollowsVelocity = true;
	
	
	
}

// Called when the game starts or when spawned
void AWakProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this,&AWakProjectile::OnComponentBeginOverlap);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Overlap);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	//필요한 함수 : 제한시간을 걸어서 Destroy 시키는 함수.
	UE_LOG(LogTemp,Warning,TEXT("Projectile Begin Play"));
}

// Called every frame
void AWakProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AWakProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//1번 방식. Target정보만 가지고 처리는 어빌리티에서.
	if(AWAKTestCharacter* Target = Cast<AWAKTestCharacter>(OtherActor))
	{
		FGameplayEventData Payload;
		Payload.Target = Target;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner,FWAKGameplayTags::Get().Event_ProjectileHit,Payload);

		//Niagara Effect 재생 후 끝나면 파괴 or Niagara는 따로 만들어서 재생 시키고 이건 파괴
		/*
		ProjectileMovementComponent->Velocity = FVector(0,0,0);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,FTimerDelegate::CreateLambda([&]()
		{
			Destroy();
		}),1.f,false);
	*/
	}

	//2번 방식. 처리도 여기에서
	if(AWAKTestCharacter* Target = Cast<AWAKTestCharacter>(OtherActor))
	{
		if(GetOwner() != OtherActor) //Owner를 AvatarActor로 설정해야 함.
		{
			UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
			OwnerASC->BP_ApplyGameplayEffectSpecToTarget(HitEffectSpecHandle,Target->GetAbilitySystemComponent());
		}
	}
}

