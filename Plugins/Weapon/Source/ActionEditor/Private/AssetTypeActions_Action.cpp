#include "AssetTypeActions_Action.h"

//#include "ActionAsset.h"
#include "ActionAssetEditor.h"


FAssetTypeActions_Action::FAssetTypeActions_Action(EAssetTypeCategories::Type InCategory) :
	Name(FText::FromString("Asset")), Color(FColor::Black), Category(InCategory)
{
}

FText FAssetTypeActions_Action::GetName() const
{
	return Name;
}

UClass* FAssetTypeActions_Action::GetSupportedClass() const
{
	return UDataAsset::StaticClass();
}

FColor FAssetTypeActions_Action::GetTypeColor() const
{
	return Color;
}

uint32 FAssetTypeActions_Action::GetCategories()
{
	return Category;
}

/*void FAssetTypeActions_Action::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	if(InObjects.Num() == 0)
		return;

	//FActionAssetEditor::OpenWindow(InObjects[0]->GetName());
}*/
