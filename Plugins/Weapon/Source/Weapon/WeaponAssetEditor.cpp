#include "WeaponAssetEditor.h"

#include "Weapons/CWeaponAsset.h"

const FName FWeaponAssetEditor::EditorName = "WeaponAssetEditor";

TSharedPtr<FWeaponAssetEditor> FWeaponAssetEditor::Instance = nullptr;

//창을 열어줌
void FWeaponAssetEditor::OpenWindow(FString InAssetName)
{
	//이미 열린 창이 있으면 닫음
	if(Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}

	Instance = MakeShareable(new FWeaponAssetEditor());
	Instance->Open(InAssetName);
}

void FWeaponAssetEditor::Shutdown()
{
	if(Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}
}

//창을 초기화 하고 열어줌
void FWeaponAssetEditor::Open(FString InAssetName)
{
	//레이아웃 설정, 탭 매니저에서 탭을 관리해줌
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("WeaponAssetEditor_Layout")
	->AddArea
	(
		FTabManager::NewPrimaryArea()
	);
	
	//에디터 초기화
	InitAssetEditor
	(EToolkitMode::Standalone
		, TSharedPtr<IToolkitHost>()
		, EditorName
		, layout
		, true							//메뉴 바가 보일것인지
		, true							//툴바 영역 보일것인지
		, NewObject<UCWeaponAsset>()			//편집할 애셋
	);

	/*Standalon : 독릭적인 창, WorldCentric : 창 안에 갇혀있는 창*/
}

void FWeaponAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

//작업표시줄에 뜨는 창 이름
FName FWeaponAssetEditor::GetToolkitFName() const
{
	return EditorName;
}

FText FWeaponAssetEditor::GetBaseToolkitName() const
{
	return FText::FromName(EditorName);
}

FString FWeaponAssetEditor::GetWorldCentricTabPrefix() const
{
	return EditorName.ToString();
}

//창 색상 지정
FLinearColor FWeaponAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0, 1);
}
