// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealLearningEditorTarget : TargetRules
{
	public UnrealLearningEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;
		ExtraModuleNames.Add("FirstPerson");
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		ExtraModuleNames.AddRange(new string[] { "Minecraft", "PickupsTest", "DataTablesTest", "SavingTest", "Portals", "DemoUMG", "GuardAI" });
	}
}
