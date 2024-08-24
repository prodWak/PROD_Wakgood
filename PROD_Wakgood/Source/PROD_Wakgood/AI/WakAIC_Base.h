
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "WakAIC_Base.generated.h"

/**
 * 
 */
UCLASS()
class PROD_WAKGOOD_API AWakAIC_Base : public AAIController
{
	GENERATED_BODY()

	const FName HomePosKey;
	const FName PatrolPosKey;
	const FName TargetKey;

public:
	AWakAIC_Base();
	
	const FName GetHomePosKey() const { return HomePosKey; }
	const FName GetPatrolPosKey() const { return PatrolPosKey; }
	const FName GetTargetKey() const { return TargetKey; }

};
