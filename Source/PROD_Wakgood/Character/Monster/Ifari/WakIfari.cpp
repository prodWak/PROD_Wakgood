// Fill out your copyright notice in the Description page of Project Settings.


#include "WakIfari.h"


AWakIfari::AWakIfari()
{
}

void AWakIfari::Attack()
{
	OnAttackDelegate.Broadcast();
}
