#include "WeaponCommand.h"

#include "WeaponAssetEditor.h"

#include "WeaponEditorStyle.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Modules/ModuleManager.h"

FWeaponCommand::FWeaponCommand()
	: TCommands("WeaponCommand", FText::FromString("Weapon Asset Editor"), NAME_None, FEditorStyle::GetStyleSetName())
{
	Command = MakeShareable(new FUICommandList());
}

FWeaponCommand::~FWeaponCommand()
{
	if(Command.IsValid())
		Command.Reset();

	if(Extender.IsValid())
		Extender.Reset();
}

void FWeaponCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(Id, "Weapon", "Weapon Asset Editor", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE

	Command->MapAction(Id, FExecuteAction::CreateRaw(this, &FWeaponCommand::ToolBar_Clicked), FCanExecuteAction());
}

void FWeaponCommand::Startup()
{
	FWeaponCommand::RegisterCommands();

	Extender = MakeShareable(new FExtender());

	FToolBarExtensionDelegate toolbar = FToolBarExtensionDelegate::CreateRaw(this, &FWeaponCommand::ToolBar_Added);
	Extender->AddToolBarExtension("Settings", EExtensionHook::After, Command, toolbar);
	
	//Extender 등록
	FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
}

void FWeaponCommand::ToolBar_Added(FToolBarBuilder& InBuilder)
{
	//구분선 추가
	InBuilder.AddSeparator();
	InBuilder.AddToolBarButton(Id, NAME_None,  FText::FromString("Weapon"),FText::FromString("Weapon Asset Editor"), FWeaponEditorStyle::Get()->GetToolBarIcon(), NAME_None);
}

void FWeaponCommand::ToolBar_Clicked()
{
	FWeaponAssetEditor::OpenWindow();
}

