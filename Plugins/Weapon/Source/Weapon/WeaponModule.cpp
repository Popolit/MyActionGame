#include "WeaponModule.h"

#include "AssetTypeActions_Weapon.h"

#include "WeaponStyle.h"
#include "WeaponCommand.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "FWeaponModule"

void FWeaponModule::StartupModule()
{
	FWeaponStyle::Get();

	Command = MakeShareable(new FWeaponCommand());
	Command->Startup();
	
	IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type type = assetTools.RegisterAdvancedAssetCategory("Weapon", FText::FromName("Weapon"));
	
	AssetTypeActions = MakeShareable(new FAssetTypeActions_Weapon(type));
	assetTools.RegisterAssetTypeActions(AssetTypeActions.ToSharedRef());
}

void FWeaponModule::ShutdownModule()
{
	if(Command.IsValid())
		Command.Reset();

	if(AssetTypeActions.IsValid())
		AssetTypeActions.Reset();	
	FWeaponStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWeaponModule, Weapon)