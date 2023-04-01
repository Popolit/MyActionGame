#pragma once

#include "CoreMinimal.h"
#include "CAction_Combo.h"
#include "CAction_Combo_Sword.generated.h"

UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Combo_Sword : public UCAction_Combo
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
};
