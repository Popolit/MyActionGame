#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class WEAPONEDITOR_API FWeaponDetailsView : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	UClass *Type;

private:
	//ȭ���� ���ŵ� ������ 
	static bool RefreshByCheckBoxes;
};
