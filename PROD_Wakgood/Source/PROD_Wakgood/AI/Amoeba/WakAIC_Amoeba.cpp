// Fill out your copyright notice in the Description page of Project Settings.


#include "WakAIC_Amoeba.h"

#include "PROD_Wakgood/Character/Monster/Amoeba/WakAmoeba.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AWakAIC_Amoeba::Amoeba_HomePosKey(TEXT("Amoeba_HomePos"));
const FName AWakAIC_Amoeba::Amoeba_PatrolPosKey(TEXT("Amoeba_PatrolPos"));
const FName AWakAIC_Amoeba::Amoeba_CanTransformKey(TEXT("Amoeba_CanTransform"));

AWakAIC_Amoeba::AWakAIC_Amoeba()
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
		else
		{
			// GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, FString("BeginPlay"));
			// OwningPawn->SetCanTransformation(true);
			// OwningPawn->CheckTransformation();
		}
	}
}
