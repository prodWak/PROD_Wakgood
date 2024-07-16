// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/GameplayEffectTestActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "..\..\Public\AbilitySystem\WAKASC.h"
#include "WAKTag.h"
#include "AbilitySystem/WAKAttributeSet.h"

// Sets default values
AGameplayEffectTestActor::AGameplayEffectTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TestTypeTag = FWAKGameplayTags::Get().Character_Type_Iron;
	TestSM = CreateDefaultSubobject<UStaticMeshComponent>("Test StaticMesh");
	SetRootComponent(TestSM);
	OverlapBox = CreateDefaultSubobject<UBoxComponent>("Test Only Box Component");
	OverlapBox->SetBoxExtent(FVector(32,32,32));
	OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OverlapBox->SetCollisionProfileName(FName("OverlapAllDynamic"));
	OverlapBox->SetupAttachment(TestSM);
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this,&AGameplayEffectTestActor::BeginOverlap);
	ASC = CreateDefaultSubobject<UWAKASC>("ASC");
	ASC->CurrentFormTag = FWAKGameplayTags::Get().Character_Type_Iron;
	ASC->AddLooseGameplayTag(ASC->CurrentFormTag);
	AttributeSet = CreateDefaultSubobject<UWAKAttributeSet>("AttributeSet");
}

// Called when the game starts or when spawned
void AGameplayEffectTestActor::BeginPlay()
{
	Super::BeginPlay();
	ASC->InitAbilityActorInfo(this,this);
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
	UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage(),GameplayEffectClass);
	if (TargetASC == nullptr) return;
	check(GameplayEffectClass);
	

	FGameplayEffectContextHandle EffectHandle = ASC->MakeEffectContext();
	EffectHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass,1,EffectHandle);
	FActiveGameplayEffectHandle ActiveHandle = ASC->ApplyGameplayEffectToTarget(Effect,TargetASC,UGameplayEffect::INVALID_LEVEL,EffectHandle);
}
void AGameplayEffectTestActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	check(GameplayEffect);
	ApplyEffectToTarget(OtherActor,GameplayEffect);
}

