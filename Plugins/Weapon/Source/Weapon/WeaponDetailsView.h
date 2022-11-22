#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class WEAPON_API FWeaponDetailsView : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	UClass *Type;

private:
	//화면이 갱신될 때마다 
	static bool RefreshByCheckBoxes;
};
