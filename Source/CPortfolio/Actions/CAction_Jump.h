#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "CAction_Jump.generated.h"

UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Jump : public UAction
{
	GENERATED_BODY()
public:
	virtual void BeginAction() override;
public:
	virtual void KeyPressed() override;
	virtual void KeyReleased() override;
};
