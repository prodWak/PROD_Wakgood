// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTTaskNode_TurnToTarget.h"

#include "PROD_Wakgood/AI/Dakdulgi/WakAIC_Dakdulgi.h"
#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"
#include "PROD_Wakgood/Character/Monster/Dakdulgi/WakDakdulgi.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTTaskNode_TurnToTarget::UWakBTTaskNode_TurnToTarget()
{
	NodeName = TEXT("Dakdulgi_TurnToTarget");
}

EBTNodeResult::Type UWakBTTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AWakDakdulgi* Dakdulgi = Cast<AWakDakdulgi>(OwnerComp.GetAIOwner()->GetPawn());
	AWakDebugPlayer* Target = Cast<AWakDebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AWakAIC_Dakdulgi::Dakdulgi_TargetKey));

	if (Dakdulgi != nullptr && Target != nullptr)
	{
		FVector LookVector = Target->GetActorLocation() - Dakdulgi->GetActorLocation();
		LookVector.Z = 0.0f;
		
		FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
		Dakdulgi->SetActorRotation(FMath::RInterpTo(Dakdulgi->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));
		
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
