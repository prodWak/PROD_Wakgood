// Fill out your copyright notice in the Description page of Project Settings.


#include "WakPoopDog.h"

#include "Runtime/Engine/Public/EngineUtils.h"

AWakPoopDog::AWakPoopDog()
{

}

void AWakPoopDog::BusterCall()
{
    if (GetIsBusterCalled())
    {
        UE_LOG(LogTemp, Warning, TEXT("It's Already Called"));
        return;
    }

    // Play Crying Animation
    // 

    for (TActorIterator<AMonster_Base> It(GetWorld()); It; ++It)
    {
        // using too many resources need to change
        // Ignore Self
        if (AWakPoopDog* Ignore = Cast<AWakPoopDog>(*It))
        {
            return;
        }
        
        UE_LOG(LogTemp, Warning, TEXT("Monster Name : %s"), *It->GetName());
        
        if (AMonster_Base* Others = Cast<AMonster_Base>(*It))
        {
            Others->SetBusterCall(true);
        }
    }
}
