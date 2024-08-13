// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_Lani.h"

#include "BehaviorTree/BlackboardComponent.h"

AWakAIC_Lani::AWakAIC_Lani()
	: Lani_HomePosKey(TEXT("Lani_HomePos"))
	, Lani_PatrolPosKey(TEXT("Lani_PatrolPos"))
	, Lani_TargetKey(TEXT("Lani_Target"))
	, Lani_IsDamagedKey(TEXT("Lani_IsDamaged"))
{
	
}

void AWakAIC_Lani::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_Lani, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(Lani_HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_Lani))
		{
			UE_LOG(LogTemp, Error, TEXT("Behavior Tree is not working"));
		}
	}
}
