// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/GameplayEffectTestActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem\WAKASC.h"
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
	
	OverlapBox->SetCollisionProfileName(FName("OverlapAllDynamic"));
	OverlapBox->SetupAttachment(RootComponent);
	OverlapBox->SetGenerateOverlapEvents(false);

	OnActorBeginOverlap.AddUniqueDynamic(this,&AGameplayEffectTestActor::BeginOverlap);
	//OverlapBox->OnComponentBeginOverlap.AddDynamic(this,&AGameplayEffectTestActor::BeginOverlap);

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


void AGameplayEffectTestActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//Gameplay Effect Test용 
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	//UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage(),GameplayEffectClass);
	if (TargetASC == nullptr) return;
	check(GameplayEffectClass);
	

	FGameplayEffectContextHandle EffectHandle = ASC->MakeEffectContext();
	EffectHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass,1,EffectHandle);
	//ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),TargetASC);
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	//FActiveGameplayEffectHandle ActiveHandle = ASC->ApplyGameplayEffectToTarget(Effect,TargetASC,UGameplayEffect::INVALID_LEVEL,EffectHandle);
}
void AGameplayEffectTestActor::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//콜리전 설정을 Pawn에만 반응하게 안하면 Overlap 이벤트를 여러번 발생시킴.
	check(GameplayEffect);
	ApplyEffectToTarget(OtherActor,GameplayEffect);
}

