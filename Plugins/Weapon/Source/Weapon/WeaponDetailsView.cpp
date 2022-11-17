#include "WeaponDetailsView.h"

TSharedRef<IDetailCustomization> WeaponDetailsView::MakeInstance()
{
	return MakeShareable(new WeaponDetailsView());
}

void WeaponDetailsView::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	
}
