// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_Lani.h"

#include "BehaviorTree/BlackboardComponent.h"

AWakAIC_Lani::AWakAIC_Lani()
	: IsDamagedKey(TEXT("IsDamaged"))
{
	
}

void AWakAIC_Lani::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_Lani, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(GetHomePosKey(), InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_Lani))
		{
			UE_LOG(LogTemp, Error, TEXT("Behavior Tree is not working"));
		}
	}
}
