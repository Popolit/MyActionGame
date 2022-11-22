#include "WeaponAssetEditor.h"

#include "SWeaponListView.h"
#include "WeaponDetailsView.h"
#include "WeaponEquipmentData.h"
#include "Weapons/CWeaponAsset.h"

const FName FWeaponAssetEditor::EditorName = "WeaponAssetEditor";
const FName FWeaponAssetEditor::ListViewTabId = "ListView";
const FName FWeaponAssetEditor::DetailsTabId = "Details";

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
	ListView = SNew(SWeaponListView)
		.OnWeaponListViewSelectedItem(this, &FWeaponAssetEditor::WeaponListViewSelectedItem);

	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	prop.RegisterCustomPropertyTypeLayout("EquipmentData", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FWeaponEquipmentData::MakeInstance));
	prop.NotifyCustomizationModuleChanged();
	
	FDetailsViewArgs args(false, false, true, FDetailsViewArgs::ObjectsUseNameArea);
	args.ViewIdentifier = "WeaponAssetEditorDetailsView";
	DetailsView = prop.CreateDetailView(args);

	FOnGetDetailCustomizationInstance detailsView = FOnGetDetailCustomizationInstance::CreateStatic(&FWeaponDetailsView::MakeInstance);
	DetailsView->SetGenericLayoutDetailsDelegate(detailsView);
	
	//���̾ƿ� ����, �� �Ŵ������� ���� ��������
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("WeaponAssetEditor_Layout")
	->AddArea
	(

		//���� ����
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)	//��ġ ����
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.1f)			//���ٸ� ���� ������ �� 1/10 ������ ���
			->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
		)
		//Main ����
		->Split
		(
			//Asset List View ����
			FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.175f)
				->AddTab(ListViewTabId, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
			//Details ����
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.825f)
				->AddTab(DetailsTabId, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
		)
	);

	UCWeaponAsset* asset = nullptr;

	//�̸��� ���� = ���ٿ��� ������
	if(InAssetName.Len() > 0)
	{
		
	}
	//�̸��� �ִ� = ������ �ּ��� ������
	else
	{
		
	}
	//������ �ʱ�ȭ
	InitAssetEditor
	(EToolkitMode::Standalone		//Standalone : �������� â, WorldCentric : â �ȿ� �����ִ� â
		, TSharedPtr<IToolkitHost>()
		, EditorName
		, layout
		, true							//�޴� �ٰ� ���ϰ�����
		, true							//���� ���� ���ϰ�����
		, NewObject<UCWeaponAsset>()			//������ �ּ�
	);

	DetailsView->SetObject(asset);
}

bool FWeaponAssetEditor::OnRequestClose()
{
	if(FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		prop.UnregisterCustomPropertyTypeLayout("EquipmentData");
		prop.NotifyCustomizationModuleChanged();
	}
		
	if(ListView.IsValid())
		ListView.Reset();

	if(DetailsView.IsValid())
		DetailsView.Reset();
	return true;
}


//���� ���, ���� ����
void FWeaponAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	//SharedPtr�� �������̼��� ����
	//CreateRaw : �Ϲ� �����Ϳ� ���� �������̼�
	//CreateSP : SharedFromThis�� �����Ǵ� this SharedPtr�� ���� �������̼�
	FOnSpawnTab tab = FOnSpawnTab::CreateSP(this, &FWeaponAssetEditor::Spawn_ListViewTab);
	InTabManager->RegisterTabSpawner(ListViewTabId, tab);

	FOnSpawnTab tab2 = FOnSpawnTab::CreateSP(this, &FWeaponAssetEditor::Spawn_DetailsTab);
	InTabManager->RegisterTabSpawner(DetailsTabId, tab2);
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

//����Ʈ �� �� ����
TSharedRef<SDockTab> FWeaponAssetEditor::Spawn_ListViewTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
	.Content()
	[
		ListView.ToSharedRef()
	];
}

TSharedRef<SDockTab> FWeaponAssetEditor::Spawn_DetailsTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
	.Content()
	[
		DetailsView.ToSharedRef()
	];
}

void FWeaponAssetEditor::WeaponListViewSelectedItem(FWeaponRowDataPtr InPtr)
{
	
}
