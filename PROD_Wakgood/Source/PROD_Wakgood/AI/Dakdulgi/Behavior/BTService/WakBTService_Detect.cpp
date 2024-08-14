// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTService_Detect.h"

#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

#include "PROD_Wakgood/AI/Dakdulgi/WakAIC_Dakdulgi.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UWakBTService_Detect::UWakBTService_Detect()
{
	NodeName = TEXT("Dakdulgi_Detect");
	Interval = 1.0f;
}

void UWakBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	DetectLogic(OwnerComp);
}

void UWakBTService_Detect::DetectLogic(UBehaviorTreeComponent& OwnerComp)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		UWorld* world = ControllingPawn->GetWorld();
		FVector Center = ControllingPawn->GetActorLocation();\
		float Radius = 600.0f;

		if (world != nullptr)
		{
			TArray<FOverlapResult> OverlapResults;
			FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);

			bool bResult = world->OverlapMultiByChannel(
				OverlapResults,
				Center,
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel1,
				FCollisionShape::MakeSphere(Radius),
				CollisionQueryParam
			);

			DrawDebugSphere(world, Center, Radius, 16, FColor::Red, false, 0.2f);

			if (bResult)
			{
				for (auto const& OverlapResult : OverlapResults)
				{
					AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OverlapResult.GetActor());
					if (Target != nullptr && Target->GetController()->IsPlayerController())
					{
						OwnerComp.GetBlackboardComponent()->SetValueAsObject(AWakAIC_Dakdulgi::Dakdulgi_TargetKey, Target);
						DrawDebugSphere(world, Center, Radius, 16, FColor::Green, false, 0.2f);
						return;
					}
				}
			}
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(AWakAIC_Dakdulgi::Dakdulgi_TargetKey, nullptr);
		}
	}
}
