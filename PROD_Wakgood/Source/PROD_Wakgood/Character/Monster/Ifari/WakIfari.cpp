// Fill out your copyright notice in the Description page of Project Settings.


#include "WakIfari.h"

#include "PROD_Wakgood/Character/Player/WakDebugPlayer.h"


AWakIfari::AWakIfari()
{
}

void AWakIfari::MeleeAttack(float Damage)
{
	Super::MeleeAttack(Damage);

	OnAttackDelegate.Broadcast();
}
