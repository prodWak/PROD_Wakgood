// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\AbilitySystem\Abilities\WAKGA.h"


void UWAKGA::ActivateAbilityAndChangeWeapon()
{
	//외형변경, ex) 무기변경 생긴거 변경.
	AWAKTestCharacter* Character = Cast<AWAKTestCharacter>(GetAvatarActorFromActorInfo());
	if(Character)
	{
		//Character->AbilityActivateByTag();
		Character->ChangeWeaponByTag();
	}
}

