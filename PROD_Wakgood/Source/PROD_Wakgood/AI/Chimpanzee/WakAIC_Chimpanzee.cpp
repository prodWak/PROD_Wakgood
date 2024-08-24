// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_Chimpanzee.h"

#include "PROD_Wakgood/Character/Monster/Chimpanzee/WakChimpanzee.h"

#include "BehaviorTree/BlackboardComponent.h"

AWakAIC_Chimpanzee::AWakAIC_Chimpanzee()
{

}

void AWakAIC_Chimpanzee::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (OwningPawn = Cast<AWakChimpanzee>(InPawn))
	{
		OwningPawn->StartIncreaseAngryGaugeTimer();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AIOwner"));
	}

	UBlackboardComponent* BLACKBOARD = Blackboard.Get();

	if (UseBlackboard(BB_Chimpanzee, BLACKBOARD))
	{
		BLACKBOARD->SetValueAsVector(GetHomePosKey(), InPawn->GetActorLocation());
		if (!RunBehaviorTree(BT_Chimpanzee))
		{
			UE_LOG(LogTemp, Warning, TEXT("BehaviorTree is not working"));
		}
	}
}
