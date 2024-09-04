// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CCS_TestTask : ModuleRules
{
	public CCS_TestTask(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
