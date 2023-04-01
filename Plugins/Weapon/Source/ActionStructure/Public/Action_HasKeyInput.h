
#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "IKeyInput.h"
#include "Action_HasKeyInput.generated.h"

UCLASS(Abstract, HideDropdown)
class ACTIONSTRUCTURE_API UAction_HasKeyInput : public UAction, public IIKeyInput
{
	GENERATED_BODY()
public:
	virtual void KeyPressed() override {}
	virtual void KeyReleased() override {}
};



