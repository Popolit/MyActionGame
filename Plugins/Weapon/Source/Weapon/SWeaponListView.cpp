#include "SWeaponListView.h"
#include "EngineUtils.h"
#include "Widgets/Input/SSearchBox.h"

#include "Weapons/CWeaponAsset.h"


void SWeaponTableRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView)
{
	Row = InArgs._Row;

	SMultiColumnTableRow<FWeaponRowDataPtr>::Construct
	(
		FSuperRowType::FArguments().Style(FEditorStyle::Get(), "TableView.DarkRow"),
		OwnerTableView
	);
}

TSharedRef<SWidget> SWeaponTableRow::GenerateWidgetForColumn(const FName& InColumnName)
{
	FString str;
	if(InColumnName ==FName("Index"))
		str = FString::FromInt(Row->Index);
	else if(InColumnName == FName("Context"))
		str = Row->Context;

	FString toolTip;
	if(!!Row->Asset)
		toolTip = Row->Asset->GetPathName();

	return SNew(SVerticalBox) + SVerticalBox::Slot()
	.AutoHeight()
	.Padding(4)
	.VAlign(VAlign_Center)
	[
		SNew(STextBlock)
		.Text(FText::FromString(str))
		.ToolTipText(FText::FromString(toolTip))
	];
}

//===============================================================================================

void SWeaponListView::Construct(const FArguments& InArgs)
{
	//Slate Argument 전달 문법
	OnWeaponListViewSelectedItem = InArgs._OnWeaponListViewSelectedItem;
	
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(2, 0)
		[
			SNew(SBox)
			[
				SAssignNew(SearchBox, SSearchBox)
				.SelectAllTextWhenFocused(true)
				.OnTextChanged(this, &SWeaponListView::OnTextChanged)
				.OnTextCommitted(this, &SWeaponListView::OnTextCommitted)
			]
		]
		+ SVerticalBox::Slot()
		.FillHeight(1)
		[
			SAssignNew(ListView, SWeaponListViewRow)	//SNew와 달리 할당이 가능함
			.ListItemsSource(&RowDatas)
			.OnGenerateRow(this, &SWeaponListView::OnGenerateRow)	//어떻게 보여줄지 (델리게이션)
			.OnSelectionChanged(this, &SWeaponListView::OnSelectionChanged)
			.HeaderRow
			(
				SNew(SHeaderRow)				//HeaderRow 추가
				+ SHeaderRow::Column("Index")
				.DefaultLabel(FText::FromString(""))
				.ManualWidth(50)
				+ SHeaderRow::Column("Context")
				.DefaultLabel(FText::FromString("Asset Name"))
			)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBox)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Right)
			.Padding(FMargin(8, 2))
			[
				SNew(STextBlock)
				.Text(this, &SWeaponListView::GetAssetCount)
			]
		]
	];

	ReadAssets();
}



//행의 갯수만큼 콜
TSharedRef<ITableRow> SWeaponListView::OnGenerateRow(FWeaponRowDataPtr InRow, const TSharedRef<STableViewBase>& InTable)
{
	return SNew(SWeaponTableRow, InTable)
		.Row(InRow);
}

FWeaponRowDataPtr SWeaponListView::GetRowDataPtrByName(FString const& InName)
{
	if(!HasDataPtrs())
		return nullptr;

	for(FWeaponRowDataPtr ptr : RowDatas)
	{
		if(ptr->Context == InName)
			return ptr;
	}

	return nullptr;
}

void SWeaponListView::SelectDataPtr(UCWeaponAsset* InAsset)
{
	if(!HasDataPtrs())
		return;

	for(FWeaponRowDataPtr ptr : RowDatas)
	{
		if(ptr->Asset == InAsset)
		{
			ListView->SetSelection(ptr);
			return;
		}
	}
}

FString SWeaponListView::SelectedRowDataPtrName()
{
	TArray<FWeaponRowDataPtr> ptrs = ListView->GetSelectedItems();

	if(ptrs.Num() == 0)
		return "";
	return ptrs[0]->Asset->GetName();
}

void SWeaponListView::ReadAssets()
{
	RowDatas.Empty();

	TArray<UObject*> objects;

	//타입을 불러올 때 클래스, 애셋을 불러올 땐 Regular
	EngineUtils::FindOrLoadAssetsByPath("/Game/Weapons/", objects, EngineUtils::ATL_Regular);

	int32 index = 0;
	for(UObject* obj : objects)
	{
		UCWeaponAsset* asset = Cast<UCWeaponAsset>(obj);
		if(asset == nullptr)
			continue;

		FString name = asset->GetName();

		//검색 필터
		if(SearchText.IsEmpty() == false)
		{
			//검색 필터에서 걸러짐
			if(name.Contains(SearchText.ToString()) == false)
				continue;
		}
		RowDatas.Add(FWeaponRowData::Make(++index, name, asset));
	}

	//정렬기준
	RowDatas.Sort([](const FWeaponRowDataPtr& A, const FWeaponRowDataPtr& B)
	{
		return A->Index < B->Index;
	});

	ListView->RequestListRefresh();
}

FText SWeaponListView::GetAssetCount() const
{
	FString str = FString::Printf(L"%d Assets", RowDatas.Num());
	
	return FText::FromString(str);
}

//검색 글자 변경시마다 해당하는 애셋 갱신
void SWeaponListView::OnTextChanged(const FText& InText)
{
	if(SearchText.CompareToCaseIgnored(InText) == 0)
		return;

	SearchText = InText;
	ReadAssets();
}

void SWeaponListView::OnTextCommitted(const FText& InText, ETextCommit::Type InType)
{
	OnTextChanged(InText);
}

void SWeaponListView::OnSelectionChanged(FWeaponRowDataPtr InPtr, ESelectInfo::Type InType)
{
	if(InPtr== nullptr || InPtr->Asset == nullptr)
		return;

	OnWeaponListViewSelectedItem.ExecuteIfBound(InPtr);	//바운드 되어있으면 실행	
}
