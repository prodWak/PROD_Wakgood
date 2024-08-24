// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTService_Neugeuja_Detect.h"

#include "PROD_Wakgood/AI/Neugeuja/WakAIC_Neugeuja.h"
#include "PROD_Wakgood/Character/Monster/Neugeuja/WakNeugeuja.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UWakBTService_Neugeuja_Detect::UWakBTService_Neugeuja_Detect()
{
	NodeName = TEXT("Neugeuja_Detect");
	Radius = 600.0f;
	Interval = 1.0f;
}

void UWakBTService_Neugeuja_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	DetectLogic(OwnerComp);
}

void UWakBTService_Neugeuja_Detect::DetectLogic(UBehaviorTreeComponent& OwnerComp)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AWakNeugeuja* AIOwner = Cast<AWakNeugeuja>(ControllingPawn);
	if (ControllingPawn != nullptr && AIOwner != nullptr && !AIOwner->IsTeleporting())
	{
		AWakAIC_Neugeuja* AIController = Cast<AWakAIC_Neugeuja>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));

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
