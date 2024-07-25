#pragma once

#include "CoreMinimal.h"
#include "WakBaseCharacter.h"
#include "WakPlayerCharacter.generated.h"

class UAbilitySystemComponent;

UCLASS()
class PROD_WAKGOOD_API AWakPlayerCharacter : public AWakBaseCharacter
{
	GENERATED_BODY()

public:
	AWakPlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
