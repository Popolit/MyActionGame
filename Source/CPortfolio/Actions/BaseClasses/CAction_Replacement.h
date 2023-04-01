#pragma once

#include "CoreMinimal.h"
#include "CAction_Base.h"
#include "IKeyInput.h"
#include "Interfaces/CI_ToggleEventHandler.h"
#include "CAction_Replacement.generated.h"

DECLARE_DELEGATE_OneParam(FOnActionReplacementTrigger, UCAction_Base*)
DECLARE_DELEGATE(FOnActionRevertTrigger)

//어떤 이벤트가 있으면 HasReplacement의 Action을 자신으로 교체
UCLASS(Abstract, HideDropdown)
class CPORTFOLIO_API UCAction_Replacement : public UCAction_Base, public IIKeyInput, public ICI_ToggleEventHandler
{
	GENERATED_BODY()
friend class UCAction_HasReplacement;
	
public:
	UCAction_Replacement();

public:
	virtual void EndAction() override;

	virtual void KeyPressed() override {}
	virtual void KeyReleased() override {}
	
private:
	virtual void HandleEvent(bool IsEventOn) override;
	virtual void BindDelegations(UCAction_HasReplacement* InObject, void(UCAction_HasReplacement::* InOnFunction)(UCAction_Base*), void (UCAction_HasReplacement::* InOffFunction)());

protected:
	bool IsReplaced;
	FOnActionReplacementTrigger OnActionReplacementTrigger;
	FOnActionRevertTrigger OnActionRevertTrigger;
};
