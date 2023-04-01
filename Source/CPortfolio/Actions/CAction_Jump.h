#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/CAction_Base.h"
#include "IKeyInput.h"
#include "CAction_Jump.generated.h"

UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Jump : public UCAction_Base, public IIKeyInput
{
	GENERATED_BODY()
public:
	virtual void BeginAction() override;
public:
	virtual void KeyPressed() override;
	virtual void KeyReleased() override;
};
