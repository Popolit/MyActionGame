#pragma once

#include "CoreMinimal.h"

class FActionAssetEditor : public FAssetEditorToolkit
{
public:
	FActionAssetEditor();

public:
	//Override
	FName GetToolkitFName() const override final;	
	FText GetBaseToolkitName() const override final;
	FString GetWorldCentricTabPrefix() const override final;
	FLinearColor GetWorldCentricTabColorScale() const override final;

	
/*private:
	static TSharedPtr<FActionAssetEditor> Instance;*/
private:
	const FName ToolkitFName;
	const FLinearColor WorldCentricTabColorScale;
};
