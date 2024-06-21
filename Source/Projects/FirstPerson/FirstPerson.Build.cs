// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FirstPerson : ModuleRules
{
	public FirstPerson(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
