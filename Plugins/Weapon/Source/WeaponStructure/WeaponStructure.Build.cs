using System.Reflection;
using UnrealBuildTool;

public class WeaponStructure : ModuleRules
{
	public WeaponStructure(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);
				
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"ActionStructure",
			}
		);
	}
}
