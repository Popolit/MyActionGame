#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/CAction_Base.h"
#include "IKeyInput.h"
#include "Interfaces/CI_EventHandler.h"
#include "Interfaces/CI_ToggleEventHandler.h"
#include "CAction_Guard.generated.h"

class UCStateComponent;

UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Guard : public UCAction_Base, public IIKeyInput, public ICI_EventHandler, public ICI_ToggleEventHandler
{
	GENERATED_BODY()

public:
	UCAction_Guard();
	
public:
	virtual void BeginPlay() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;
	virtual void KeyPressed() override;
	virtual void KeyReleased() override;

public:
	virtual void HandleEvent() override;
	virtual void HandleEvent(bool IsEventOn) override;

private:
	UCStateComponent* StateComponent;
	bool bCanParry;
};
