// Fill out your copyright notice in the Description page of Project Settings.


#include "WakDakdulgi.h"

AWakDakdulgi::AWakDakdulgi()
{
	
}

void AWakDakdulgi::Attack()
{
	OnAttackDelegate.Broadcast();
}