// Fill out your copyright notice in the Description page of Project Settings.


#include "WakJuMob.h"

#include "Runtime/Engine/Public/EngineUtils.h"

AWakJuMob::AWakJuMob()
{
}

void AWakJuMob::CallAllJuMob()
{
    for (TActorIterator<AWakJuMob> It(GetWorld()); It; ++It)
    {
        It->SetBusterCall(true);
        UE_LOG(LogTemp, Warning, TEXT("Name : %s"), *It->GetName());
    }
}

void AWakJuMob::MeleeAttack(float Damage)
{
    Super::MeleeAttack(Damage);

    OnAttackDelegate.Broadcast();
}
