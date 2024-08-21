// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_Neugeuja.h"

#include "BehaviorTree/BlackboardComponent.h"

AWakAIC_Neugeuja::AWakAIC_Neugeuja()
	: Neugeuja_HomePosKey(TEXT("Neugeuja_HomePos"))
	, Neugeuja_PatrolPosKey(TEXT("Neugeuja_PatrolPos"))
	, Neugeuja_TargetKey(TEXT("Neugeuja_Target"))
{

}

void AWakAIC_Neugeuja::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_Neugeuja, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(Neugeuja_HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_Neugeuja))
		{
			UE_LOG(LogTemp, Error, TEXT("BehaviorTree is not working"));
		}
	}
}
