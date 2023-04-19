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

//모듈의 시작
void FWeaponEditorModule::StartupModule()
{
	//싱글톤 에디터 스타일 가져오기
	FWeaponEditorStyle::Get();

	//새로운 Weapon Editor Command 생성
	Command = MakeShareable(new FWeaponCommand());
	Command->Startup();

	//Module Manager에 있는 AssetTools 가져오기
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	//AssetTools가 WeaponEditor 모듈을 등록하고 해당하는 타입을 반환
	EAssetTypeCategories::Type const Type = AssetTools.RegisterAdvancedAssetCategory(ModuleName, FText::FromName(ModuleName));

	//Eidtor의 Asset Type Action을 생성하고 등록함
	AssetTypeActions = MakeShareable(new FAssetTypeActions_Weapon(Type));
	AssetTools.RegisterAssetTypeActions(AssetTypeActions.ToSharedRef());
}

//모듈을 종료
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