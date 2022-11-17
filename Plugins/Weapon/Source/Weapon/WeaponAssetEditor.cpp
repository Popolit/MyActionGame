#include "WeaponAssetEditor.h"

#include "Weapons/CWeaponAsset.h"

const FName FWeaponAssetEditor::EditorName = "WeaponAssetEditor";

TSharedPtr<FWeaponAssetEditor> FWeaponAssetEditor::Instance = nullptr;

//â�� ������
void FWeaponAssetEditor::OpenWindow(FString InAssetName)
{
	//�̹� ���� â�� ������ ����
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

//â�� �ʱ�ȭ �ϰ� ������
void FWeaponAssetEditor::Open(FString InAssetName)
{
	//���̾ƿ� ����, �� �Ŵ������� ���� ��������
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("WeaponAssetEditor_Layout")
	->AddArea
	(
		FTabManager::NewPrimaryArea()
	);
	
	//������ �ʱ�ȭ
	InitAssetEditor
	(EToolkitMode::Standalone
		, TSharedPtr<IToolkitHost>()
		, EditorName
		, layout
		, true							//�޴� �ٰ� ���ϰ�����
		, true							//���� ���� ���ϰ�����
		, NewObject<UCWeaponAsset>()			//������ �ּ�
	);

	/*Standalon : �������� â, WorldCentric : â �ȿ� �����ִ� â*/
}

void FWeaponAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

//�۾�ǥ���ٿ� �ߴ� â �̸�
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

//â ���� ����
FLinearColor FWeaponAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0, 1);
}
