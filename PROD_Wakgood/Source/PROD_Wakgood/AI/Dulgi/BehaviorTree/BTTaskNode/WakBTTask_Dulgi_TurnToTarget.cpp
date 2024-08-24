// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTask_Dulgi_TurnToTarget.h"

#include "PROD_Wakgood/AI/Dulgi/WakAIC_Dulgi.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTTask_Dulgi_TurnToTarget::UWakBTTask_Dulgi_TurnToTarget()
{
	NodeName = TEXT("Dulgi_TurnToTarget");

	TargetRot = FRotator(0, 0, 0);
	ControllingPawnRot = FRotator(0, 0, 0);
}

EBTNodeResult::Type UWakBTTask_Dulgi_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_Dulgi* AIController = Cast<AWakAIC_Dulgi>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));
		AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AIController->GetTargetKey()));

		if (Target != nullptr)
		{
			FVector LookVector = Target->GetActorLocation() - ControllingPawn->GetActorLocation();
			LookVector.Z = 0;
			TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
			ControllingPawnRot = ControllingPawn->GetActorRotation();

			ControllingPawn->SetActorRotation(FMath::RInterpTo(
			ControllingPawn->GetActorRotation(), TargetRot, ControllingPawn->GetWorld()->GetDeltaSeconds(), 10.0f));
		}
	}

	if ((TargetRot - ControllingPawnRot).Yaw <= 0.1)
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
