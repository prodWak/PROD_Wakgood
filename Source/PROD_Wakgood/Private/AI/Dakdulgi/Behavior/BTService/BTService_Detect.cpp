// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Dakdulgi/Behavior/BTService/BTService_Detect.h"

#include "Character/Player/Wakgood_DebugPlayer.h"
#include "Character/Monster/Dakdulgi/Wakgood_Dakdulgi.h"

#include "AI/Dakdulgi/AIC_Dakdulgi.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	DetectRogic(OwnerComp);
}

void UBTService_Detect::DetectRogic(UBehaviorTreeComponent& OwnerComp)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		UWorld* world = ControllingPawn->GetWorld();
		FVector Center = ControllingPawn->GetActorLocation();
		float DetectRadius = 600.0f;

		if (world != nullptr)
		{
			TArray<FOverlapResult> OverlapResults;
			FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
			CollisionQueryParam.AddIgnoredActor(OwnerComp.GetAIOwner()->GetPawn());

			bool bResult = world->OverlapMultiByChannel(
				OverlapResults,
				Center,
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel1,
				FCollisionShape::MakeSphere(DetectRadius),
				CollisionQueryParam
			);

			DrawDebugSphere(world, Center, DetectRadius, 16, FColor::Red, false, 0.2f);

			if (bResult)
			{
				for (auto const& OverlapResult : OverlapResults)
				{
					AWakgood_DebugPlayer* Target = Cast<AWakgood_DebugPlayer>(OverlapResult.GetActor());
					if (Target != nullptr && Target->GetController()->IsPlayerController())
					{
						OwnerComp.GetBlackboardComponent()->SetValueAsObject(AAIC_Dakdulgi::TargetKey, Target);

						DrawDebugSphere(world, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
						DrawDebugPoint(world, Target->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
						DrawDebugLine(world, ControllingPawn->GetActorLocation(), Target->GetActorLocation(), FColor::Blue, false, 0.2f);
						
						return;
					}
				}
			}
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(AAIC_Dakdulgi::TargetKey, nullptr);
		}
	}
}
