// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTService_BatDan_Detect.h"

#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "PROD_Wakgood/Character/Monster/BatDan/WakBatDan.h"

#include "PROD_Wakgood/AI/BatDan/WakAIC_BatDan.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

UWakBTService_BatDan_Detect::UWakBTService_BatDan_Detect()
{
	NodeName = TEXT("BatDan_Detect");
}

void UWakBTService_BatDan_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	DetectLogic(OwnerComp);
}

void UWakBTService_BatDan_Detect::DetectLogic(UBehaviorTreeComponent& OwnerComp)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AWakBatDan* AIOwner = Cast<AWakBatDan>(ControllingPawn);

	if (ControllingPawn != nullptr)
	{
		UWorld* world = ControllingPawn->GetWorld();
		FVector Center = ControllingPawn->GetActorLocation();
		float Radius = 500.0f;

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
						OwnerComp.GetBlackboardComponent()->SetValueAsObject(AWakAIC_BatDan::BatDan_TargetKey, Target);
						DrawDebugSphere(world, Center, Radius, 16, FColor::Green, false, 0.2f);
						AIOwner->SetTarget(Target);
						return;
					}
				}
			}
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(AWakAIC_BatDan::BatDan_TargetKey, nullptr);
			AIOwner->SetTarget(nullptr);
			AIOwner->GetAttackDetector()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}
