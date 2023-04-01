#include "WeaponDetailsView.h"

#include "DetailLayoutBuilder.h"
#include "WeaponAsset.h"

TSharedRef<IDetailCustomization> FWeaponDetailsView::MakeInstance()
{
	return MakeShareable(new FWeaponDetailsView());
}

void FWeaponDetailsView::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	Type = UWeaponAsset::StaticClass();
}

