// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTService_Ifari_Detect.h"

#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

#include "PROD_Wakgood/AI/Ifari/WakAIC_Ifari.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UWakBTService_Ifari_Detect::UWakBTService_Ifari_Detect()
{
	NodeName = (TEXT("Ifari_Detect"));
	Interval = 1.0f;
	Radius = 600.0f;
}

void UWakBTService_Ifari_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	DetectLogic(OwnerComp);
}

void UWakBTService_Ifari_Detect::DetectLogic(UBehaviorTreeComponent& OwnerComp)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_Ifari* AIController = Cast<AWakAIC_Ifari>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));

		UWorld* world = ControllingPawn->GetWorld();
		FVector Center = ControllingPawn->GetActorLocation();

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

			DrawDebugSphere(world, Center, Radius, 16, FColor::Red, false, 1.0f, 1);

			if (bResult)
			{
				for (auto const& OverlapResult : OverlapResults)
				{
					AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OverlapResult.GetActor());
					if (Target != nullptr && Target->GetController()->IsPlayerController())
					{
						OwnerComp.GetBlackboardComponent()->SetValueAsObject(AIController->GetTargetKey(), Target);
						DrawDebugSphere(world, Center, Radius, 16, FColor::Green, false, 1.0f, 1);
						return;
					}
				}
			}
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(AIController->GetTargetKey(), nullptr);
		}
	}
}
