using UnrealBuildTool;

public class PickupsTest : ModuleRules
{
    public PickupsTest(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "FirstPerson" });
    }
}