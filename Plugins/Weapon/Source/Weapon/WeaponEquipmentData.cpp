#include "WeaponEquipmentData.h"

#include "DetailWidgetRow.h"

TSharedRef<IPropertyTypeCustomization> FWeaponEquipmentData::MakeInstance()
{
	return MakeShareable(new FWeaponEquipmentData());
}

void FWeaponEquipmentData::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow,
                                           IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	
	InHeaderRow
	.DiffersFromDefault(false)
	.NameContent()
	[
		InPropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MaxDesiredWidth(500)
	[
		SNew(STextBlock)
	];
}

void FWeaponEquipmentData::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle,
	IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
}
