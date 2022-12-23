#include "WeaponDetailsView.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "Weapons/CWeaponAsset.h"

TSharedRef<IDetailCustomization> FWeaponDetailsView::MakeInstance()
{
	return MakeShareable(new FWeaponDetailsView());
}

void FWeaponDetailsView::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	Type = UCWeaponAsset::StaticClass();
}

