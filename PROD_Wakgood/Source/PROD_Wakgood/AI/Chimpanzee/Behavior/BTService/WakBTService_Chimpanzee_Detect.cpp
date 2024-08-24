// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTService_Chimpanzee_Detect.h"

#include "PROD_Wakgood/AI/Chimpanzee/WakAIC_Chimpanzee.h"
#include "PROD_Wakgood/Character/Monster/Chimpanzee/WakChimpanzee.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UWakBTService_Chimpanzee_Detect::UWakBTService_Chimpanzee_Detect()
{
	NodeName = TEXT("Chimpanzee_Detect");
	Interval = 1.0f;
	Radius = 600.0f;
}

void UWakBTService_Chimpanzee_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	DetectLogic(OwnerComp);
}

void UWakBTService_Chimpanzee_Detect::DetectLogic(UBehaviorTreeComponent& OwnerComp)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AWakChimpanzee* AIOwner = Cast<AWakChimpanzee>(ControllingPawn);
	if (ControllingPawn != nullptr && AIOwner != nullptr)
	{
		AWakAIC_Chimpanzee* AIController = Cast<AWakAIC_Chimpanzee>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));

		if (AIOwner != nullptr && AIOwner->GetIsBusterCalled())
		{
			AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(UGameplayStatics::GetPlayerPawn(ControllingPawn->GetWorld(), 0));
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(AIController->GetTargetKey(), Target);
			// Change Mesh
			// 
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
					if (Target != nullptr && Target->GetController()->IsPlayerController() && AIOwner->GetCanAttack())
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
