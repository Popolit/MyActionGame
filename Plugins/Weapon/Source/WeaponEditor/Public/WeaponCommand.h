#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"


class FUICommandList;

//자식 클래스를 알기 위한 template 클래스 상속
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
