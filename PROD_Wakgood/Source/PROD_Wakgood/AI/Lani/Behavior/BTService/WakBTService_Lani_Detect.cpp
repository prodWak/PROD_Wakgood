// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTService_Lani_Detect.h"

#include "PROD_Wakgood/AI/Lani/WakAIC_Lani.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "PROD_Wakgood/Character/Monster/Lani/WakLani.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

#include "Kismet/GameplayStatics.h"

UWakBTService_Lani_Detect::UWakBTService_Lani_Detect()
{
	NodeName = TEXT("Lani_Detect");
	Interval = 1.0f;
	Radius = 600.0f;
}

void UWakBTService_Lani_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	DetectLogic(OwnerComp);
}

void UWakBTService_Lani_Detect::DetectLogic(UBehaviorTreeComponent& OwnerComp)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_Lani* AIController = Cast<AWakAIC_Lani>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));
		if (AIController != nullptr)
		{
			AWakLani* AIOwner = Cast<AWakLani>(ControllingPawn);
			if (AIOwner != nullptr && AIOwner->GetIsBusterCalled())
			{
				AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(UGameplayStatics::GetPlayerPawn(ControllingPawn->GetWorld(), 0));
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AIController->GetTargetKey(), Target);
				return;
			}

			UWorld* world = ControllingPawn->GetWorld();
			FVector Center = ControllingPawn->GetActorLocation();

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
}
