// Fill out your copyright notice in the Description page of Project Settings.


#include "WakGA_Wakgood_Q.h"

#include "Actor/WakProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Player/WakPlayerController.h"

class AWakProjectile;

void UWakGA_Wakgood_Q::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// 아리 Q 같은 느낌.
	//Is Smart Casting을 통해 만약 is Smart Casting 이라면 화살표 스폰
	bool IsSmartCasting = true; // Test용 

	if(!IsSmartCasting)
	{
		
	}
	else
	{
		InputPressed(Handle,ActorInfo,ActivationInfo);
	}
	
}

void UWakGA_Wakgood_Q::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UWakGA_Wakgood_Q::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	FVector Direction = Cast<AWakPlayerController>(ActorInfo->PlayerController.Get())->GetRotationUnderCursor();
	Direction.Z = GetAvatarActorFromActorInfo()->GetActorLocation().Z; // 높이를 일치 시켜주기.
	FRotator DirectionRotator = Direction.Rotation();
	
	//Actor Spawn
	FTransform SpawnTransform;
	SpawnTransform.SetRotation(DirectionRotator.Quaternion());
	SpawnTransform.SetLocation(GetAvatarActorFromActorInfo()->GetActorLocation());
	
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = ActorInfo->AvatarActor.Get();

	AWakProjectile* Projectile = GetWorld()->SpawnActorDeferred<AWakProjectile>(
	AWakProjectile::StaticClass(),
	SpawnTransform,
	GetOwningActorFromActorInfo(),
	Cast<APawn>(GetOwningActorFromActorInfo()),
	ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	Projectile->GetProjectileMovementComponent()->InitialSpeed = 300.f;
	


		
	
	
}
