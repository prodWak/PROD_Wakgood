// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTService_Detect.h"

#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

#include "PROD_Wakgood/AI/Dakdulgi/WakAIC_Dakdulgi.h"
#include "PROD_Wakgood/Character/Monster/Dakdulgi/WakDakdulgi.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UWakBTService_Detect::UWakBTService_Detect()
{
	NodeName = TEXT("Dakdulgi_Detect");
	Interval = 1.0f;
	Radius = 600.0f;
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
		AWakAIC_Dakdulgi* AIController = Cast<AWakAIC_Dakdulgi>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));

		if (AWakDakdulgi* AIOwner = Cast<AWakDakdulgi>(ControllingPawn))
		{
			if (AIOwner != nullptr && AIOwner->GetIsBusterCalled())
			{
				AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(UGameplayStatics::GetPlayerPawn(ControllingPawn->GetWorld(), 0));
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AIController->GetTargetKey(), Target);
				return;
			}
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
						return;
					}
				}
			}
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(AIController->GetTargetKey(), nullptr);
		}
	}
}
