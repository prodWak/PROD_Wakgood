#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransfer.generated.h"

UCLASS()
class PROD_WAKGOOD_API ALevelTransfer : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelTransfer();

protected:
	// virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FName TransferLevelName;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString TransferGameMode;

	UPROPERTY()
	class UBoxComponent* TransferVolume;

};
