#pragma once

#include "CoreMinimal.h"

class FActionAssetEditor : public FAssetEditorToolkit
{
public:
	FActionAssetEditor();

public:
	//Override
	virtual FName GetToolkitFName() const override final;	
	virtual FText GetBaseToolkitName() const override final;
	virtual FString GetWorldCentricTabPrefix() const override final;
	virtual FLinearColor GetWorldCentricTabColorScale() const override final;

	
/*private:
	static TSharedPtr<FActionAssetEditor> Instance;*/
private:
	const FName ToolkitFName;
	const FLinearColor WorldCentricTabColorScale;
};
