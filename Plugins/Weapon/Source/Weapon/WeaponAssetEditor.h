#pragma once

#include "CoreMinimal.h"
#include "SWeaponListView.h"
#include "Toolkits/AssetEditorToolkit.h"

class WEAPON_API FWeaponAssetEditor : public FAssetEditorToolkit
{
public:
	static void OpenWindow(FString InAssetName = "");
	static void Shutdown();

private:
	void Open(FString InAssetName);

protected:
	//â�� ������ �� ���� ���� (false ��ȯ �� â�� ������ ����)
	bool OnRequestClose() override;
	
public:
	//���� �������ִ� �Լ�
	void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	//���� ���� �Լ� �������̵�
	FName GetToolkitFName() const override;
	FText GetBaseToolkitName() const override;
	FString GetWorldCentricTabPrefix() const override;
	FLinearColor GetWorldCentricTabColorScale() const override;

private:
	TSharedRef<SDockTab> Spawn_ListViewTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> Spawn_DetailsTab(const FSpawnTabArgs& InArgs);

private:
	void WeaponListViewSelectedItem(FWeaponRowDataPtr InPtr);
	
private:
	static TSharedPtr<FWeaponAssetEditor> Instance;
	
private:
	static const FName EditorName;
	static const FName ListViewTabId;
	static const FName DetailsTabId;

private:
	TSharedPtr<class SWeaponListView> ListView;
	TSharedPtr<class IDetailsView> DetailsView;
};
