// Fill out your copyright notice in the Description page of Project Settings.


#include "WakBaseNPC2.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/SWidget.h"
#include "Engine/DataTable.h"
#include "WakDialogueWidget.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AWakBaseNPC2::AWakBaseNPC2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	SphereComponent->SetupAttachment(GetRootComponent());

	DialogueWidgetClass = nullptr;
	TextWidget = nullptr;

	
	
}

// Called when the game starts or when spawned
void AWakBaseNPC2::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AWakBaseNPC2::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AWakBaseNPC2::OnEndOverlap);

	RowNum = DialogueDataTable->GetRowNames();
	InstanceNPCName = GetActorLabel();
}

// Called every frame
void AWakBaseNPC2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWakBaseNPC2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AWakBaseNPC2::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character && IsInteracting == false) 
		{
			Interaction(OtherActor);
			
		}

	}
}

void AWakBaseNPC2::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsInteracting == true)
	{
		ExitInteraction();
	}
	EndDialogue();
}

void AWakBaseNPC2::Interaction(AActor* target)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "interaction");
	if (IsInteracting)
	{
		ExitInteraction();
	}
	else if (!IsInteracting)
	{
		EnterInteraction();
	}
}
void AWakBaseNPC2::EnterInteraction()
{
	IsInteracting = true;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, "EnterInteraction");
}

void AWakBaseNPC2::ExitInteraction()
{
	IsInteracting = false;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, "ExitInteraction");
}

// Dialogue Start
void AWakBaseNPC2::StartDialogue()
{
	if (DialogueWidgetClass)
	{
		if (TextWidget == nullptr)
		{
			TextWidget = CreateWidget<UWakDialogueWidget>(GetWorld(), DialogueWidgetClass);
		}

		if (TextWidget != nullptr && (TextWidget->IsInViewport()))
		{
			TextWidget->MainTextBox->SetText(FText::FromString(NextText()));
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, "SetText");

		}
		else if (TextWidget !=nullptr && !(TextWidget->IsInViewport()))
		{
			TextWidget->MainTextBox->SetText(FText::FromString(NextText()));
			TextWidget->AddToViewport();
			
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "Something Wrong");
		}
	}
}
// Dialogue End
void AWakBaseNPC2::EndDialogue()
{
	if (TextWidget != nullptr)
	{
		TextWidget->RemoveFromParent();
		/*TextWidget = nullptr;*/
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, "removed");
		idx = 0;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, "NotRemoved");
	}
}

// Game내 NPCInstance의 name과 DataTable내의 NPCName이 같아야 함.
FString AWakBaseNPC2::NextText()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "Start NextText()");
	
	for (FName& Names : RowNum)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, FString::FromInt(idx));

		FDialogueStruct* Row = DialogueDataTable->FindRow<FDialogueStruct>(Names, TEXT("Context"));

		// Text가 빈칸이면 대화종료
		if (Row && Row->Text == "\0" && Row->NPCName == InstanceNPCName)
		{
			EndDialogue();
		}
		else if (Row && Row->Index == idx && Row->NPCName == InstanceNPCName)
		{
			NextDialogue = *Row->Text;
			idx++;
			break;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, "There's no Row");
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue,NextDialogue);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue,InstanceNPCName);
	

	return NextDialogue;
}
