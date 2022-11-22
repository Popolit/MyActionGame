using UnrealBuildTool;

public class CPortfolio : ModuleRules
{
	public CPortfolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

		PublicIncludePaths.Add(ModuleDirectory);
		PublicDependencyModuleNames.AddRange (new string[] 
			{
				"GameplayAbilities",
				"GameplayTags",
				"GameplayTasks",
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore",
				"Niagara",
			});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
