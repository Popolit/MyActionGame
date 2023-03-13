#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"


class FUICommandList;

class WEAPONEDITOR_API FWeaponCommand : public TCommands<FWeaponCommand>
{
public:
	FWeaponCommand();
	~FWeaponCommand();

	void RegisterCommands() override;

public:
	void Startup();
	
private:
	void ToolBar_Added(FToolBarBuilder& InBuilder);
	void ToolBar_Clicked();

public:
	TSharedPtr<FExtender> Extender;
	
	TSharedPtr<FUICommandList> Command;
	TSharedPtr<FUICommandInfo> Id;
};
