using UnrealBuildTool;

public class CHelpers : ModuleRules
{
	public CHelpers(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

		PublicIncludePaths.Add(ModuleDirectory);
		PublicDependencyModuleNames.AddRange (new string[] 
		{
			"Core",
			"CoreUObject", 
			"Engine",
			"Niagara"
		});
	}
}
