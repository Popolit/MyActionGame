#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class WEAPON_API WeaponDetailsView : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
};
