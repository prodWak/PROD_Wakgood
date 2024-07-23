// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Dakdulgi/Behavior/BTTask/BTTaskNode_Attack.h"

#include "AI/Dakdulgi/AIC_Dakdulgi.h"
#include "Character/Monster/Dakdulgi/Wakgood_Dakdulgi.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	NodeName = TEXT("Dakdulgi_Attack");

	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AWakgood_Dakdulgi* Dakdulgi = Cast<AWakgood_Dakdulgi>(OwnerComp.GetAIOwner()->GetPawn());
	if (Dakdulgi == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// 이 노드가 처음 실행될 때 공격을 1회만 하고 무한루프에 들어감, 감지반경 재진입 시 정상작동함 수정 필요함
	// 틱에서 !IsAttacking 일 때 FinisnLatentTask 실행해서 Succeeded 반환했는데 왜 걸리는거지... 순서가 잘못됐나

	IsAttacking = true;
	Dakdulgi->Attack();
	Dakdulgi->OnAttackEnd.AddLambda([this]()->void {
		IsAttacking = false;
		});

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
