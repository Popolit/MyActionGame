using UnrealBuildTool;

public class CPortfolio : ModuleRules
{
	public CPortfolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);
		PublicDependencyModuleNames.AddRange (new string[] 
			{
				"GameplayAbilities",
				"GameplayTags",
				"GameplayTasks",
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore" 
			});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
