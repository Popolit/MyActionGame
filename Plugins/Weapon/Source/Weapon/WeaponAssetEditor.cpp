#include "WeaponAssetEditor.h"

#include "WeaponDetailsView.h"
#include "Weapons/CWeaponAsset.h"

const FName FWeaponAssetEditor::EditorName = "WeaponAssetEditor";
const FName FWeaponAssetEditor::ListViewTabId = "ListView";
const FName FWeaponAssetEditor::DetailsTabId = "Details";

TSharedPtr<FWeaponAssetEditor> FWeaponAssetEditor::Instance = nullptr;

//창을 열어줌
void FWeaponAssetEditor::OpenWindow(FString InAssetName)
{
	//이미 열린 창이 있으면 닫음
	if(Instance.IsValid())
	{
		//창은 이미 열림, 리스트뷰의 아이템 선택
		if(Instance->ListView.IsValid())
		{
			FWeaponRowDataPtr ptr = nullptr;

			//애셋 네임이 존재
			if(0 < InAssetName.Len())
				ptr = Instance->ListView->GetRowDataPtrByName(InAssetName);

			if(ptr == nullptr)
				ptr = Instance->ListView->GetFirstDataPtr();

			Instance->ListView->SelectDataPtr(ptr->Asset);

			return;
		}
		//컨텐츠 브라우저 선택 상황
		else
		{
			Instance->CloseWindow();
			Instance.Reset();
			Instance = nullptr;
		}
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
	ListView = SNew(SWeaponListView)
		.OnWeaponListViewSelectedItem(this, &FWeaponAssetEditor::WeaponListViewSelectedItem);

	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	prop.NotifyCustomizationModuleChanged();
	
	FDetailsViewArgs args(false, false, true, FDetailsViewArgs::ObjectsUseNameArea);
	args.ViewIdentifier = "WeaponAssetEditorDetailsView";
	DetailsView = prop.CreateDetailView(args);

	FOnGetDetailCustomizationInstance detailsView = FOnGetDetailCustomizationInstance::CreateStatic(&FWeaponDetailsView::MakeInstance);
	DetailsView->SetGenericLayoutDetailsDelegate(detailsView);
	
	//레이아웃 설정, 탭 매니저에서 탭을 관리해줌
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("WeaponAssetEditor_Layout")
	->AddArea
	(

		//툴바 영역
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)	//배치 방향
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.1f)			//툴바를 위해 위에서 약 1/10 영역을 사용
			->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
		)
		//Main 영역
		->Split
		(
			//Asset List View 영역
			FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.175f)
				->AddTab(ListViewTabId, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
			//Details 영역
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

	//이름이 있다 지정한 애셋을 열었음
	if(0 < InAssetName.Len())
	{
		FWeaponRowDataPtr ptr = ListView->GetRowDataPtrByName(InAssetName);

		//이미 열려있는 애셋임
		if(ListView->SelectedRowDataPtrName() == InAssetName)
			return;

		if(ptr.IsValid() == false)
			asset = ListView->GetFirstDataPtr()->Asset;
		else
			asset = ptr->Asset;			
	}
	//이름이 없다 = 툴바에서 열었음
	else
	{
		asset = ListView->GetFirstDataPtr()->Asset;
	}
	//에디터 초기화
	InitAssetEditor
	(EToolkitMode::Standalone		//Standalone : 독릭적인 창, WorldCentric : 창 안에 갇혀있는 창
		, TSharedPtr<IToolkitHost>()
		, EditorName
		, layout
		, true							//메뉴 바가 보일것인지
		, true							//툴바 영역 보일것인지
		, NewObject<UCWeaponAsset>()			//편집할 애셋
	);

	ListView->SelectDataPtr(asset);
}

bool FWeaponAssetEditor::OnRequestClose()
{
	if(DetailsView.IsValid())
	{
		//GEditor = 에디터 전역을 관리하는 객체
		if(!!GEditor && !!GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
			GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->NotifyAssetClosed(GetEditingObject(), this);
		
	}
	if(FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		prop.NotifyCustomizationModuleChanged();
	}
		
	if(ListView.IsValid())
		ListView.Reset();

	if(DetailsView.IsValid())
		DetailsView.Reset();
	return true;
}


//탭을 등록, 정의 해줌
void FWeaponAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	//SharedPtr로 델리게이션을 연결
	//CreateRaw : 일반 포인터에 대한 델리게이션
	//CreateSP : SharedFromThis로 관리되는 this SharedPtr에 대한 델리게이션
	FOnSpawnTab tab = FOnSpawnTab::CreateSP(this, &FWeaponAssetEditor::Spawn_ListViewTab);
	InTabManager->RegisterTabSpawner(ListViewTabId, tab);

	FOnSpawnTab tab2 = FOnSpawnTab::CreateSP(this, &FWeaponAssetEditor::Spawn_DetailsTab);
	InTabManager->RegisterTabSpawner(DetailsTabId, tab2);
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

//리스트 뷰 탭 생성
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
	//빈공간 클릭
	if(InPtr == nullptr)
		return;

	//창을 열었을 때 다른 에디팅중인 애셋을 제거해줌
	if(!!GetEditingObject())
		RemoveEditingObject(GetEditingObject());

	AddEditingObject(InPtr->Asset);
	DetailsView->SetObject(InPtr->Asset);
}
