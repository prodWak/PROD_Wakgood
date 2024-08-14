// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_Amoeba.h"

#include "PROD_Wakgood/Character/Monster/Amoeba/WakAmoeba.h"
#include "BehaviorTree/BlackboardComponent.h"

AWakAIC_Amoeba::AWakAIC_Amoeba()
	: Amoeba_HomePosKey(TEXT("Amoeba_HomePos"))
	, Amoeba_PatrolPosKey(TEXT("Amoeba_PatrolPos"))
	, Amoeba_CanTransformKey(TEXT("Amoeba_CanTransform"))
{

}

void AWakAIC_Amoeba::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwningPawn = Cast<AWakAmoeba>(InPawn);
	check(OwningPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_Amoeba, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(Amoeba_HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_Amoeba))
		{
			UE_LOG(LogTemp, Error, TEXT("BehaviorTree is not working"));
		}
	}
}
