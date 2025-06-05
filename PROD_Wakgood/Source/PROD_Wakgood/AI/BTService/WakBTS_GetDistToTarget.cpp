// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService/WakBTS_GetDistToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTS_GetDistToTarget::UWakBTS_GetDistToTarget()
{
	NodeName = TEXT("Get Dist To Target");

	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	Interval = 0.f;
	RandomDeviation = 0.f;

	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());
	OutDistToTargetKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, OutDistToTargetKey));
}

void UWakBTS_GetDistToTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (const UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InTargetActorKey.ResolveSelectedKey(*BBAsset);
		OutDistToTargetKey.ResolveSelectedKey(*BBAsset);
	}
}

FString UWakBTS_GetDistToTarget::GetStaticDescription() const
{
	const FString InTargetKey = InTargetActorKey.SelectedKeyName.ToString();
	const FString OutTargetKey = OutDistToTargetKey.SelectedKeyName.ToString();
	return FString::Printf(TEXT("Get distance to %s key %s"), *InTargetKey, *OutTargetKey);
}

void UWakBTS_GetDistToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName);
	const AActor* TargetActor = Cast<AActor>(ActorObject);
	const APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (TargetActor == nullptr || OwningPawn == nullptr)
	{
		return;
	}
	
	const float DistToTarget = OwningPawn->GetDistanceTo(TargetActor);

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(OutDistToTargetKey.SelectedKeyName, DistToTarget);
}
