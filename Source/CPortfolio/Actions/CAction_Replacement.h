#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "Interfaces/CI_EventHandler_Toggle.h"
#include "CAction_Replacement.generated.h"

DECLARE_DELEGATE_OneParam(FOnActionReplacementTrigger, UAction*)
DECLARE_DELEGATE(FOnActionRevertTrigger)

//어떤 이벤트가 있으면 HasReplacement의 Action을 자신으로 교체
UCLASS(Abstract, HideDropdown)
class CPORTFOLIO_API UCAction_Replacement : public UAction, public ICI_EventHandler_Toggle
{
	GENERATED_BODY()
friend class UCAction_HasReplacement;
public:
	UCAction_Replacement();

	virtual void EndAction() override;
private:
	virtual void HandleEvent(bool IsEventOn) override;
	virtual void BindDelegations(UCAction_HasReplacement* InObject, void(UCAction_HasReplacement::* InOnFunction)(UAction*), void (UCAction_HasReplacement::* InOffFunction)());

private:
	bool IsReplaced;
	FOnActionReplacementTrigger OnActionReplacementTrigger;
	FOnActionRevertTrigger OnActionRevertTrigger;
};
