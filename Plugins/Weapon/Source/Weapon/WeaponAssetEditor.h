#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class WEAPON_API FWeaponAssetEditor : public FAssetEditorToolkit
{
public:
	static void OpenWindow(FString InAssetName = "");
	static void Shutdown();

private:
	void Open(FString InAssetName);
	
public:
	//���� �������ִ� �Լ�
	void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	//���� ���� �Լ� �������̵�
	FName GetToolkitFName() const override;
	FText GetBaseToolkitName() const override;
	FString GetWorldCentricTabPrefix() const override;
	FLinearColor GetWorldCentricTabColorScale() const override;

private:
	static TSharedPtr<FWeaponAssetEditor> Instance;
	
private:
	static const FName EditorName;
};
