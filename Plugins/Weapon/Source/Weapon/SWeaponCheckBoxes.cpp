#include "SWeaponCheckBoxes.h"

#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "IDetailPropertyRow.h"
#include "Widgets/Layout/SScaleBox.h"

void SWeaponCheckBoxes::Add(FString InName, TSharedPtr<IPropertyHandle> InHandle)
{
	if(bLocked)
		return;

	InternalDatas.Add(FInternalData(InName, InHandle));
}

void SWeaponCheckBoxes::Complete_Adding()
{
	if(bLocked)
		return;
	bLocked = true;
}

void SWeaponCheckBoxes::SetUtilities(TSharedPtr<IPropertyUtilities> InUtilities)
{
	Utilities = InUtilities;
}

TSharedRef<SWidget> SWeaponCheckBoxes::Draw()
{
	TSharedPtr<SHorizontalBox> box;
	SAssignNew(box, SHorizontalBox);

	int32 InternalDatasSize = InternalDatas.Num();

	//Slate ����
	for(int32 i = 0; i < InternalDatasSize; i++)
	{
		box->AddSlot()
		.AutoWidth()
		[
			DrawCheckBox(i)
		];
	}
	
	return box.ToSharedRef();
}

//�� üũ�ڽ��� �׷��ִ� �Լ�
TSharedRef<SWidget> SWeaponCheckBoxes::DrawCheckBox(int32 InIndex)
{
	return SNew(SCheckBox)
	.IsChecked(InternalDatas[InIndex].bChecked)
	.Content()
	[
		SNew(SScaleBox)
		.Content()
		[
			SNew(STextBlock)
			.Margin(FMargin(0, 0, 10, 0))
			.Text(FText::FromString(InternalDatas[InIndex].Name))
		]
	];
}

/*
void SWeaponCheckBoxes::DrawProperties(TSharedRef<IPropertyHandle> InPropertyHandle,
	IDetailChildrenBuilder InChildBuilder)
{
	for(int32 i = 0; i < InternalDatas.Num(); i++)
	{
		if(InternalDatas[i].bChecked = false)
			continue;

		TSharedPtr<IPropertyHandle> handle = InPropertyHandle->GetChildHandle(i);
		IDetailPropertyRow& row = InChildBuilder->AddProperty(handle.ToSharedRef());

		TSharedPtr<SWidget> name;
		TSharedPtr<SWidget> value;

		row.GetDefaultWidgets(name, value);

		row.CustomWidget()
		.NameContent()
		[
			name.ToSharedRef()
		]
		.ValueContent()
		.MinDesiredWidth(300)	//ȭ���� ���ܵ� �ּ� �ʺ� ����
		[
			value.ToSharedRef()
		];
	}

}*/

