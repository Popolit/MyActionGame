#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class ACTIONEDITOR_API FAssetTypeActions_Action : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_Action(EAssetTypeCategories::Type InCategory);

	//Override
	public:
	virtual FText GetName() const override;
	/*virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;*/

public:
	//void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override; 

private:
	FText const Name;
	EAssetTypeCategories::Type const Category;
};
