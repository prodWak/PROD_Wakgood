// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_Neugeuja.h"

#include "BehaviorTree/BlackboardComponent.h"

AWakAIC_Neugeuja::AWakAIC_Neugeuja()
{

}

void AWakAIC_Neugeuja::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_Neugeuja, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(GetHomePosKey(), InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_Neugeuja))
		{
			UE_LOG(LogTemp, Error, TEXT("BehaviorTree is not working"));
		}
	}
}
