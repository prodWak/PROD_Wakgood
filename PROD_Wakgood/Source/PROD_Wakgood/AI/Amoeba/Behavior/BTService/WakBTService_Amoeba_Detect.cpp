// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTService_Amoeba_Detect.h"

#include "PROD_Wakgood/AI/Amoeba/WakAIC_Amoeba.h"
#include "PROD_Wakgood/Character/Monster/Amoeba/WakAmoeba.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UWakBTService_Amoeba_Detect::UWakBTService_Amoeba_Detect()
{
	NodeName = TEXT("Amoeba_Detect");
	Interval = 1.0f;
}

void UWakBTService_Amoeba_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	DetectLogic(OwnerComp);
}

void UWakBTService_Amoeba_Detect::DetectLogic(UBehaviorTreeComponent& OwnerComp)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AWakAmoeba* AIOwner = Cast<AWakAmoeba>(ControllingPawn);

	if (ControllingPawn != nullptr && AIOwner != nullptr)
	{
		AWakAIC_Amoeba* AIController = Cast<AWakAIC_Amoeba>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));

		UWorld* world = ControllingPawn->GetWorld();
		FVector Center = ControllingPawn->GetActorLocation();
		float Radius = 600.0f;

		if (world != nullptr)
		{
			TArray<FOverlapResult> OverlapResults;
			FCollisionQueryParams CollisionQueryParams(NAME_None, false, ControllingPawn);

			bool bResult = world->OverlapMultiByChannel(
				OverlapResults,
				Center,
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel1,
				FCollisionShape::MakeSphere(Radius),
				CollisionQueryParams
			);

			DrawDebugSphere(world, Center, Radius, 16, FColor::Red, false, 0.2f);

			if (bResult)
			{
				for (auto const& OverlapResult : OverlapResults)
				{
					AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OverlapResult.GetActor());
					if (Target != nullptr && Target->GetController()->IsPlayerController())
					{
						DrawDebugSphere(world, Center, Radius, 16, FColor::Green, false, 0.2f);
						OwnerComp.GetBlackboardComponent()->SetValueAsBool(AIController->GetCanTransformKey(), true);
						AIOwner->SetCanTransformation(true);
						return;
					}
				}
			}
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AIController->GetCanTransformKey(), false);
		}
	}
}
