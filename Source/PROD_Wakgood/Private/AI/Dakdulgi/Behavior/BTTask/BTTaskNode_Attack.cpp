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

	// �� ��尡 ó�� ����� �� ������ 1ȸ�� �ϰ� ���ѷ����� ��, �����ݰ� ������ �� �����۵��� ���� �ʿ���
	// ƽ���� !IsAttacking �� �� FinisnLatentTask �����ؼ� Succeeded ��ȯ�ߴµ� �� �ɸ��°���... ������ �߸��Ƴ�

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
