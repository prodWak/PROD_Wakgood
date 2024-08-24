// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBTService_PoopDog_IsDamaged.h"

#include "PROD_Wakgood/AI/PoopDog/WakAIC_PoopDog.h"
#include "PROD_Wakgood/Character/Monster/PoopDog/WakPoopDog.h"
#include "BehaviorTree/BlackboardComponent.h"

UWakBTService_PoopDog_IsDamaged::UWakBTService_PoopDog_IsDamaged()
{
	NodeName = TEXT("PoopDog_IsDamaged");
	Interval = 1.0f;
}

void UWakBTService_PoopDog_IsDamaged::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckIsDamaged(OwnerComp);
}

void UWakBTService_PoopDog_IsDamaged::CheckIsDamaged(UBehaviorTreeComponent& OwnerComp)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn != nullptr)
	{
		AWakAIC_PoopDog* AIController = Cast<AWakAIC_PoopDog>(UAIBlueprintHelperLibrary::GetAIController(ControllingPawn));
		AWakPoopDog* AIOwner = Cast<AWakPoopDog>(ControllingPawn);

		if (AIOwner != nullptr && AIController != nullptr)
		{
			if (AIOwner->GetIsDamaged())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AIController->GetIsDamagedKey(), true);
			}
			else
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AIController->GetIsDamagedKey(), false);
			}
		}
	}
}
