#include "WeaponDetailsView.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "SWeaponCheckBoxes.h"
#include "Weapons/CWeaponAsset.h"

TSharedRef<IDetailCustomization> FWeaponDetailsView::MakeInstance()
{
	return MakeShareable(new FWeaponDetailsView());
}

void FWeaponDetailsView::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	Type = UCWeaponAsset::StaticClass();

	//Attachment 카테고리
	/*{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Attachment", FText::FromName("Attachment"));
		category.AddProperty("AttachmentClass", Type);
	}*/
	//Equipment 카테고리
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Equipment", FText::FromName("Equipment"));
		IDetailPropertyRow& row = category.AddProperty("EquipmentData", Type);

		if(!RefreshByCheckBoxes)
		{
			//FWeaponEquipmentData::
			//TSharedPtr<SWeaponCheckBoxes> checkBoxes = FWeaponEquipmentData::CreateCheckBoxes();

			int32 index = 0;
			
		}
	}
}

