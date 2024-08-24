// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_PoopDog.h"

#include "BehaviorTree/BlackboardComponent.h"

AWakAIC_PoopDog::AWakAIC_PoopDog()
	: PoopDog_IsDamagedKey(TEXT("IsDamaged"))
{

}

void AWakAIC_PoopDog::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_PoopDog, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(GetHomePosKey(), InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_PoopDog))
		{
			UE_LOG(LogTemp, Error, TEXT("BehaviorTree is not working"));
		}
	}
}
