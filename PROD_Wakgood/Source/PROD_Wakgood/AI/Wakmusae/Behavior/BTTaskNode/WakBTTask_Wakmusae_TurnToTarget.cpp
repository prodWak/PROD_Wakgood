// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_Wakmusae_TurnToTarget.h"

#include "PROD_Wakgood/AI/Wakmusae/WakAIC_Wakmusae.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "PROD_Wakgood/Character/Monster/Wakmusae/WakWakmusae.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTTask_Wakmusae_TurnToTarget::UWakBTTask_Wakmusae_TurnToTarget()
{
	NodeName = TEXT("Wakmusae_TurnToTarget");

	TargetRot = FRotator(0, 0, 0);
	ControllingPawnRot = FRotator(0, 0, 0);
}

EBTNodeResult::Type UWakBTTask_Wakmusae_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_Wakmusae* AIController = Cast<AWakAIC_Wakmusae>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));
		AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AIController->GetTargetKey()));

		if (Target != nullptr)
		{
			FVector LookVector = Target->GetActorLocation() - ControllingPawn->GetActorLocation();
			LookVector.Z = 0;
			TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
			ControllingPawnRot = ControllingPawn->GetActorRotation();

			ControllingPawn->SetActorRotation(FMath::RInterpTo(
				ControllingPawn->GetActorRotation(), TargetRot, ControllingPawn->GetWorld()->GetDeltaSeconds(), 50.0f));
		}
	}

	if (FMath::Abs((TargetRot - ControllingPawnRot).Yaw) <= 0.1)
	{
		UE_LOG(LogTemp, Warning, TEXT("%lf"), (TargetRot - ControllingPawnRot).Yaw);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
