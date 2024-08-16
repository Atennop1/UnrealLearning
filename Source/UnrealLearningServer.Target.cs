// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealLearningServerTarget : TargetRules
{
	public UnrealLearningServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;
		ExtraModuleNames.Add("FirstPerson");
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		ExtraModuleNames.AddRange(new string[] { "Minecraft", "PickupsTest", "DataTablesTest", "SavingTest", "Portals", "DemoUMG", "GuardAI", "ThirdPerson", "DemoEffects", "DemoSound", "PhysicsSimulation", "OptimizationTest", "Network" });
	}
}
