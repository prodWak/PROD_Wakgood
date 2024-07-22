// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Dakdulgi/Behavior/BTTask/BTTaskNode_TurnToTarget.h"

#include "AI/Dakdulgi/AIC_Dakdulgi.h"
#include "Character/Player/Wakgood_DebugPlayer.h"
#include "Character/Monster/Dakdulgi/Wakgood_Dakdulgi.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_TurnToTarget::UBTTaskNode_TurnToTarget()
{
	NodeName = TEXT("TurnToTarget");
}

EBTNodeResult::Type UBTTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AWakgood_Dakdulgi* Dakdulgi = Cast<AWakgood_Dakdulgi>(OwnerComp.GetAIOwner()->GetPawn());
	AWakgood_DebugPlayer* Target = Cast<AWakgood_DebugPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AAIC_Dakdulgi::TargetKey));

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
