// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WakGA_RangedAttackBase.h"

#include "WAKTag.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Actor/WakProjectile.h"
#include "Character/WAKTestCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UWakGA_RangedAttackBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//Projectile 설정 -> 애니메이션 재생 -> 1. Spawn Projectile State를 찾으면 발사  -> Projectile에서 벽 또는 적과 충돌 시 Event 보내기
	//-> Target Data를 받으면 Target에게 Effect 적용. 
}

void UWakGA_RangedAttackBase::SpawnProjectile(FGameplayEventData Payload)
{
	SetProjectile(AbilityProjectileClass);
	UE_LOG(LogTemp,Warning,TEXT("Spawn Projectile"));
}

void UWakGA_RangedAttackBase::SetProjectile(TSubclassOf<AWakProjectile> ProjectileClass)
{
	AWAKTestCharacter* SourceCharacter = Cast<AWAKTestCharacter>(GetAvatarActorFromActorInfo());
	FName SocketName("hand_r_weapon");
	FVector CharacterLocation = SourceCharacter->GetActorLocation();
	
	FRotator Rotation = SourceCharacter->GetActorForwardVector().Rotation();
	Rotation.Pitch = 0.f;
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(CharacterLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
	
	Projectile = GetWorld()->SpawnActorDeferred<AWakProjectile>(
	ProjectileClass,
	SpawnTransform,
	GetAvatarActorFromActorInfo(),
	Cast<APawn>(GetAvatarActorFromActorInfo()),
	ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);
	
	Projectile->FinishSpawning(SpawnTransform);
	
	UE_LOG(LogTemp,Warning,TEXT("Set Projectile"));
}

void UWakGA_RangedAttackBase::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
