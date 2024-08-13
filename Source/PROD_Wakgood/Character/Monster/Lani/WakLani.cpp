// Fill out your copyright notice in the Description page of Project Settings.


#include "WakLani.h"

AWakLani::AWakLani()
{
}

void AWakLani::MeleeAttack(float Damage)
{
	Super::MeleeAttack(Damage);

	OnAttackDelegate.Broadcast();
}