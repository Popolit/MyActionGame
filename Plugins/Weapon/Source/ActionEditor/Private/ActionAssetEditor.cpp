#include "ActionAssetEditor.h"

FActionAssetEditor::FActionAssetEditor() : FAssetEditorToolkit(),
											ToolkitFName("ActionAssetEditor"),
											WorldCentricTabColorScale(FLinearColor(0, 0, 1))
{
}


FName FActionAssetEditor::GetToolkitFName() const
{
	return ToolkitFName;
}

FText FActionAssetEditor::GetBaseToolkitName() const
{
	return FText::FromName(ToolkitFName);
}

FString FActionAssetEditor::GetWorldCentricTabPrefix() const
{
	return ToolkitFName.ToString();
}

FLinearColor FActionAssetEditor::GetWorldCentricTabColorScale() const
{
	return WorldCentricTabColorScale;
}

