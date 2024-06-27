using UnrealBuildTool;

public class DemoUMG : ModuleRules
{
    public DemoUMG(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "UMG", "SlateCore", "EnhancedInput", "FirstPerson" });
    }
}