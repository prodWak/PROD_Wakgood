// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AI/WakAIController.h"

#include "WakLogChannels.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AWakAIController::AWakAIController()
{
	WakAISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("WakAISenseConfig_Sight"));
	WakAISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	WakAISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	WakAISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	WakAISenseConfig_Sight->SightRadius = 500.f;
	WakAISenseConfig_Sight->LoseSightRadius = 550.f;
	WakAISenseConfig_Sight->PeripheralVisionAngleDegrees = 90.f;
	WakAISenseConfig_Sight->SetMaxAge(5.f);

	WakAIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("WakAIPerceptionComponent"));
	WakAIPerceptionComponent->ConfigureSense(*WakAISenseConfig_Sight);
	WakAIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	WakAIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnPerceptionUpdated);
	WakAIPerceptionComponent->OnTargetPerceptionForgotten.AddUniqueDynamic(this, &ThisClass::OnPerceptionForgotten);

	// Set Team ID 
	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AWakAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* PawnToCheck = Cast<const APawn>(&Other))
	{
		const IGenericTeamAgentInterface* OtherTeamAgentInterface =
			Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());

		if (OtherTeamAgentInterface && OtherTeamAgentInterface->GetGenericTeamId() != GetGenericTeamId())
		{
			return ETeamAttitude::Hostile;
		}
	}

	return ETeamAttitude::Friendly;
}

void AWakAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!RunBehaviorTree(WakBehaviorTree))
	{
		UE_LOG(LogWak, Error, TEXT("BehaviorTree %s somehow is nor working"), *WakBehaviorTree->GetName());
	}
}

void AWakAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), Actor);
		}
	}
}

void AWakAIController::OnPerceptionForgotten(AActor* Actor)
{
	UE_LOG(LogWak, Warning, TEXT("Forgotten Actor : %s"), *Actor->GetActorNameOrLabel());
	
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), nullptr);
	}
}
