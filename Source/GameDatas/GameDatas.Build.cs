using UnrealBuildTool;

public class GameDatas : ModuleRules
{
	public GameDatas(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

		PublicIncludePaths.Add(ModuleDirectory);
		PublicDependencyModuleNames.AddRange (new string[] 
		{
			
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine",
		});
	}
}
