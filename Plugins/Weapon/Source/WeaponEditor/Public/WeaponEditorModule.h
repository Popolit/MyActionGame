#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FWeaponCommand;
class IAssetTypeActions;

/* Weapon Editor Module */
class FWeaponEditorModule : public IModuleInterface
{
public:
	FWeaponEditorModule();
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	const FName ModuleName;
	TSharedPtr<FWeaponCommand> Command;
	TSharedPtr<IAssetTypeActions> AssetTypeActions;
};
