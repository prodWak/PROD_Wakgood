// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/GameplayEffectTestActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WAKTag.h"

// Sets default values
AGameplayEffectTestActor::AGameplayEffectTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
	TestTypeTag = FWAKGameplayTags::Get().Type_Iron;
}

// Called when the game starts or when spawned
void AGameplayEffectTestActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGameplayEffectTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameplayEffectTestActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//Gameplay Effect Test용 
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1, EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
}

void AGameplayEffectTestActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	check(GameplayEffect);
	ApplyEffectToTarget(OtherActor,GameplayEffect);
}

