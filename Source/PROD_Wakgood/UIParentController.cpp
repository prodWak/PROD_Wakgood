// Fill out your copyright notice in the Description page of Project Settings.


#include "UIParentController.h"
#include "InputCoreTypes.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Application/NavigationConfig.h"

void AUIParentController::BeginPlay()
{
	Super::BeginPlay();

	//FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::A, EUINavigation::Left);
	//FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::S, EUINavigation::Down);
	//FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::W, EUINavigation::Up);
	//FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::D, EUINavigation::Right);
	//FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::J, EUINavigationAction::Accept);

	TSharedPtr<FNavigationConfig> NavConfig = FSlateApplication::Get().GetNavigationConfig();

	if (NavConfig.IsValid())
	{
		// Use Add method to add KeyEventRules
		NavConfig->KeyEventRules.Add(EKeys::A, EUINavigation::Left);
		NavConfig->KeyEventRules.Add(EKeys::S, EUINavigation::Down);
		NavConfig->KeyEventRules.Add(EKeys::W, EUINavigation::Up);
		NavConfig->KeyEventRules.Add(EKeys::D, EUINavigation::Right);

		// ¿Ö ¾È´ï?
		//NavConfig->KeyEventRules.Add(EKeys::J, static_cast<EUINavigation>(EUINavigationAction::Accept));
	}
}
