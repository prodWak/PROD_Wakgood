// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTService_Lani_IsDamaged.h"

#include "PROD_Wakgood/AI/Lani/WakAIC_Lani.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "PROD_Wakgood/Character/Monster/Lani/WakLani.h"

UWakBTService_Lani_IsDamaged::UWakBTService_Lani_IsDamaged()
{
	NodeName = TEXT("Lani_IsDamaged");
	Interval = 1.0f;
}

void UWakBTService_Lani_IsDamaged::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckIsDamaged(OwnerComp);
}

void UWakBTService_Lani_IsDamaged::CheckIsDamaged(UBehaviorTreeComponent& OwnerComp)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_Lani* AIController = Cast<AWakAIC_Lani>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));
		AWakLani* Lani = Cast<AWakLani>(ControllingPawn);
		if (AIController != nullptr && Lani != nullptr)
		{
			if (Lani->GetIsDamaged())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AIController->GetIsDamagedKey(), true);
				// TODO : Call Lani Transformation Function
			}
			else
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AIController->GetIsDamagedKey(), false);
			}
		}
	}
}
