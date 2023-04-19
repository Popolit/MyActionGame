#include "WeaponEditorModule.h"

#include "AssetTypeActions_Weapon.h"
#include "WeaponEditorStyle.h"
#include "WeaponCommand.h"

#include "IAssetTools.h"
#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "FWeaponEditorModule"


FWeaponEditorModule::FWeaponEditorModule() : ModuleName("WeaponEditor")
{
}

//����� ����
void FWeaponEditorModule::StartupModule()
{
	//�̱��� ������ ��Ÿ�� ��������
	FWeaponEditorStyle::Get();

	//���ο� Weapon Editor Command ����
	Command = MakeShareable(new FWeaponCommand());
	Command->Startup();

	//Module Manager�� �ִ� AssetTools ��������
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	//AssetTools�� WeaponEditor ����� ����ϰ� �ش��ϴ� Ÿ���� ��ȯ
	EAssetTypeCategories::Type const Type = AssetTools.RegisterAdvancedAssetCategory(ModuleName, FText::FromName(ModuleName));

	//Eidtor�� Asset Type Action�� �����ϰ� �����
	AssetTypeActions = MakeShareable(new FAssetTypeActions_Weapon(Type));
	AssetTools.RegisterAssetTypeActions(AssetTypeActions.ToSharedRef());
}

//����� ����
void FWeaponEditorModule::ShutdownModule()
{
	if(Command.IsValid())
	{
		Command.Reset();
	}
	
	if(AssetTypeActions.IsValid())
	{
		AssetTypeActions.Reset();	
	}
	
	FWeaponEditorStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWeaponEditorModule, WeaponEditor)