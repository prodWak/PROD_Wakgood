// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTService_Dulgi_Detect.h"

#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "PROD_Wakgood/Character/Monster/Dulgi/WakDulgi.h"

#include "PROD_Wakgood/AI/Dulgi/WakAIC_Dulgi.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UWakBTService_Dulgi_Detect::UWakBTService_Dulgi_Detect()
{
	NodeName = TEXT("Dulgi_Detect");
	Interval = 1.0f;
	Radius = 600.0f;
}

void UWakBTService_Dulgi_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	DetectLogic(OwnerComp);
}

void UWakBTService_Dulgi_Detect::DetectLogic(UBehaviorTreeComponent& OwnerComp)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AWakDulgi* AIOwner = Cast<AWakDulgi>(ControllingPawn);

	if (ControllingPawn != nullptr)
	{
		AWakAIC_Dulgi* AIController = Cast<AWakAIC_Dulgi>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));

		if (AIOwner != nullptr && AIOwner->GetIsBusterCalled())
		{
			AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(UGameplayStatics::GetPlayerPawn(ControllingPawn->GetWorld(), 0));
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(AIController->GetTargetKey(), Target);
			AIOwner->SetTarget(Target);
			return;
		}

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

			if (bResult)
			{
				for (auto const& OverlapResult : OverlapResults)
				{
					AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OverlapResult.GetActor());
					if (Target != nullptr && Target->GetController()->IsPlayerController())
					{
						OwnerComp.GetBlackboardComponent()->SetValueAsObject(AIController->GetTargetKey(), Target);
						AIOwner->SetIsDetectPlayer(true);
						AIOwner->SetTarget(Target);
						return;
					}
				}
			}

			OwnerComp.GetBlackboardComponent()->SetValueAsObject(AIController->GetTargetKey(), nullptr);
			AIOwner->SetIsDetectPlayer(false);
			AIOwner->SetTarget(nullptr);
		}
	}
}
