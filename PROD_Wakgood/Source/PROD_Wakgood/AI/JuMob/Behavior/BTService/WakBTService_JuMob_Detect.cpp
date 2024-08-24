// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTService_JuMob_Detect.h"

#include "PROD_Wakgood/AI/JuMob/WakAIC_JuMob.h"
#include "PROD_Wakgood/Character/Monster/JuMob/WakJuMob.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UWakBTService_JuMob_Detect::UWakBTService_JuMob_Detect()
{
	NodeName = TEXT("JuMob_Detect");
	Interval = 1.0f;
	Radius = 600.0f;
}

void UWakBTService_JuMob_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	DetectLogic(OwnerComp);
}

void UWakBTService_JuMob_Detect::DetectLogic(UBehaviorTreeComponent& OwnerComp)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_JuMob* AIController = Cast<AWakAIC_JuMob>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));

		if (AWakJuMob* AIOwner = Cast<AWakJuMob>(ControllingPawn))
		{
			if (AIOwner != nullptr && AIOwner->GetIsBusterCalled())
			{
				AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AIController->GetTargetKey(), Target);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AIController->GetIsDetectTarget(), true);
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
						OwnerComp.GetBlackboardComponent()->SetValueAsBool(AIController->GetIsDetectTarget(), true);
						return;
					}
				}
			}
		}
	}
}
