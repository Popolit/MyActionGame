#include "AssetTypeActions_Action.h"


FAssetTypeActions_Action::FAssetTypeActions_Action(EAssetTypeCategories::Type InCategory) : Name(FText::FromString("Asset")), Category(InCategory)
{
}

FText FAssetTypeActions_Action::GetName() const
{
	return Name;
}
