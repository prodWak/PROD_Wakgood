// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PROD_Wakgood : ModuleRules
{
	public PROD_Wakgood(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
