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
	//탭을 관리해주는 함수
	void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	//순수 가상 함수 오버라이딩
	FName GetToolkitFName() const override;
	FText GetBaseToolkitName() const override;
	FString GetWorldCentricTabPrefix() const override;
	FLinearColor GetWorldCentricTabColorScale() const override;

private:
	static TSharedPtr<FWeaponAssetEditor> Instance;
	
private:
	static const FName EditorName;
};
