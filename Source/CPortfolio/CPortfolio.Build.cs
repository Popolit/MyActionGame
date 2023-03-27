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
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Niagara",
			"GameDatas",
			"ActionStructure",
			"WeaponStructure"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CHelpers"
		});
	}
}
