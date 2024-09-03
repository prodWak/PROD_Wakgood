// Fill out your copyright notice in the Description page of Project Settings.


#include "WakNPCBase.h"

#include "Widgets/SWidget.h"

#include "Engine/DataTable.h"

#include "PROD_Wakgood/Game/WakDialogueDataTable.h"
#include "PROD_Wakgood/Game/WakDialogueWidget.h"
#include "PROD_Wakgood/TP_ThirdPerson/TP_ThirdPersonCharacter.h"


AWakNPCBase::AWakNPCBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	DialogueWidgetClass = nullptr;
	TextWidget = nullptr;
}

void AWakNPCBase::BeginPlay()
{
	Super::BeginPlay();

	RowNum = DialogueDataTable->GetRowNames();
	InstanceNPCName = GetActorLabel();
}

void AWakNPCBase::Interaction(AActor* target)
{	
	if (!IsInteracting)
	{
		StartDialogue();
	}
}

void AWakNPCBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
		
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ATP_ThirdPersonCharacter* OverlappingCharacter = Cast<ATP_ThirdPersonCharacter>(OtherActor);
		if(OverlappingCharacter && GetWorld())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Overlapping"), *OverlappingCharacter->GetName());
		}
	}
}

void AWakNPCBase::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	if (TextWidget)
	{
		EndDialogue();
		TextWidget = nullptr;
		
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, "TextWidget = nullptr");

	}
}

void AWakNPCBase::StartDialogue()
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

void AWakNPCBase::EndDialogue()
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

void AWakNPCBase::ExitInteraction()
{
	IsInteracting = false;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, "ExitInteraction");
	
	EndDialogue();
}

FString AWakNPCBase::NextText()
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