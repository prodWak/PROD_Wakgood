// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_BatDan.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "PROD_Wakgood/Character/Monster/BatDan/WakBatDan.h"

AWakAIC_BatDan::AWakAIC_BatDan()
{

}

void AWakAIC_BatDan::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwningPawn = Cast<AWakBatDan>(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_BatDan, BLACKBOARD))
	{
		if (!RunBehaviorTree(BT_BatDan))
		{
			UE_LOG(LogTemp, Error, TEXT("Behavior Tree is not working"));
		}
	}
}
