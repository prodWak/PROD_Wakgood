﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "WakPlayerController.h"
#include "AbilitySystem/WAKASC.h"
#include "Input/WakinputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/WAKTestCharacter.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "WAKTag.h"
#include "Components/SplineComponent.h"

AWakPlayerController::AWakPlayerController()
{
	bReplicates = true;
	ConstructorHelpers::FObjectFinder<UInputMappingContext> ContextFinder(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/ThirdPerson/Input/IMC_Default.IMC_Default'"));
	if(ContextFinder.Succeeded())
		WakContext = ContextFinder.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> MoveActionFinder(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Move.IA_Move'"));
	if(MoveActionFinder.Succeeded())
		MoveAction = MoveActionFinder.Object;

	ConstructorHelpers::FObjectFinder<UWAKInputConfig> InputConfigFinder(TEXT("/Script/PROD_Wakgood.WAKInputConfig'/Game/DataTable/DA_InputConfig.DA_InputConfig'"));
	if(InputConfigFinder.Succeeded())
		InputConfig = InputConfigFinder.Object;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	
}	

void AWakPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	AutoRun();
	GetEnemyCharacterUnderCursor();
}

void AWakPlayerController::GetEnemyCharacterUnderCursor()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Pawn,false,HitResult);
	if(HitResult.bBlockingHit)
	{
		if(TObjectPtr<AWAKTestCharacter> Target = Cast<AWAKTestCharacter>(HitResult.GetActor()))
		{
			if(HitResult.GetActor() != GetPawn())
			{
				TargetActor = Target;
			}
			else
				TargetActor = nullptr;
		}
		else
		{
			TargetActor = nullptr;
		}
	}
}

FVector AWakPlayerController::GetRotationUnderCursor()
{
	FVector MouseLocation;
	FVector MouseDirection;
	
	DeprojectMousePositionToWorld(MouseLocation,MouseDirection);

	FVector EndLocation = MouseLocation + (MouseDirection * 100.f);
	FVector StartLocation = GetPawn()->GetActorLocation();
	return (EndLocation - StartLocation).GetSafeNormal();
}

void AWakPlayerController::AutoRun()
{
	if(!bAutoRunning)
		return;
	if(APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(),ESplineCoordinateSpace::World); // 액터의 위치에서 가장 가까운 스플라인 포인트 벡터
		//Spline은 방향성을 가지고 있기 때문에 항상 앞을 가장 가까운 지점으로 잡는다.
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);
		//스플라인 상에서 가장 가까운 지점으로 이동하기 위한 방향을 가져옴.
		DrawDebugSphere(GetWorld(),LocationOnSpline,8.f,8,FColor::Red); 
		ControlledPawn->AddMovementInput(Direction);
		//특정 Actor 무시
		
		
		const float DistanceToDestination = (LocationOnSpline-CachedDestination).Length();
		if(DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
		
	}
}


void AWakPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(WakContext, 0);
	}
	SetShowMouseCursor(true);

}

void AWakPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	CreateInputComponent(UWAKInputComponent::StaticClass());
	if(InputComponent)
	{
		InputComponent->DestroyComponent();
		InputComponent = NewObject<UWAKInputComponent>(this,UWAKInputComponent::StaticClass());
		InputComponent->RegisterComponent();
	}
	if(UWAKInputComponent* WakInputComponent = Cast<UWAKInputComponent>(InputComponent))
	{
		WakInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AWakPlayerController::Move);
		WakInputComponent->BindAbilityActions(InputConfig, this, &AWakPlayerController::AbilityInputTagPressed,&AWakPlayerController::AbilityInputTagReleased);
		
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Cast Failed"));
	}
}

void AWakPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotator(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
		
	}
	
}

TObjectPtr<UWAKASC> AWakPlayerController::GetASC()
{
	if(WakAbilitySystem == nullptr)
	{
		WakAbilitySystem = Cast<UWAKASC>(GetPawn<AWAKTestCharacter>()->GetAbilitySystemComponent());
	}
	return WakAbilitySystem;
}

void AWakPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//InputComponent에 바인드 되어 있고, 입력시 InputTag가 매개변수로 들어옴.
	if(!InputTag.IsValid())
		return;
	if(InputTag.MatchesTagExact(FWAKGameplayTags::Get().InputTag_RMB))
	{
		//bTargeting = 
		bAutoRunning = false;
	}
	GetASC()->AbilityInputTagPressed(InputTag);
}

void AWakPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//InputComponent에 바인드 되어 있고, 입력시 InputTag가 매개변수로 들어옴.
	if(!InputTag.IsValid())
		return;
	if(InputTag.MatchesTagExact(FWAKGameplayTags::Get().InputTag_RMB))
	{

		if(TargetActor)
		{
			//TODO 평타 Ability
		}
		//FollowTime += GetWorld()->GetDeltaSeconds(); // 프레임마다 시간초 증가, Trigger일 때 쓰면 누른 시간 측정가능 release할때 시간을 가져오면 됨.
		//bTargeting = 
		//테스트용 우클릭 이동
		else
		{
			FHitResult HitResult;
			GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
			if(HitResult.bBlockingHit)
			{
				CachedDestination = HitResult.ImpactPoint;
			}
			if(APawn* ControlledPawn = GetPawn())
			{
				//Trigger 였다면 이걸로 
				/*const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
				ControlledPawn->AddMovementInput(WorldDirection);*/
				if(UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this,ControlledPawn->GetActorLocation(),CachedDestination))
				{
					Spline->ClearSplinePoints();
					for(const FVector& PointLoc : NavPath->PathPoints)
					{
						Spline->AddSplinePoint(PointLoc,ESplineCoordinateSpace::World);
						DrawDebugSphere(GetWorld(),PointLoc,8.f,8,FColor::Green,false,5.f);
					}
					CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num()-1]; //목적지까지의 경로를 찾기 -> 목적지까지 못 닿는 경우 마지막 포인트로 가게 될 것. 
					bAutoRunning = true;
				
				}
			}
		}
	}
	else
		GetASC()->AbilityInputTagReleased(InputTag);
}
