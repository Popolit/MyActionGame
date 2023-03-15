#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "TraceAnalysis/Private/Store/AsioFile.h"

class FWeaponCommand;
class IAssetTypeActions;

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
