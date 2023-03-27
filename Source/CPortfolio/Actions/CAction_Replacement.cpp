#include "CAction_Replacement.h"

#include "CAction_HasReplacement.h"


UCAction_Replacement::UCAction_Replacement() : UAction(), IsReplaced(false)
{
}

void UCAction_Replacement::EndAction()
{
	Super::EndAction();

	HandleEvent(false);
}

void UCAction_Replacement::HandleEvent(bool IsEventOn)
{
	if(IsEventOn && OnActionReplacementTrigger.IsBound())
	{
		OnActionReplacementTrigger.Execute(this);
		return;
	}
	if(!IsEventOn && OnActionRevertTrigger.IsBound())
	{
		OnActionRevertTrigger.Execute();
	}
}

void UCAction_Replacement::BindDelegations(UCAction_HasReplacement* InObject,
                                          void(UCAction_HasReplacement::* InOnFunction)(UAction*), void (UCAction_HasReplacement::* InOffFunction)())
{
	OnActionReplacementTrigger.BindUObject(InObject, InOnFunction);
	OnActionRevertTrigger.BindUObject(InObject, InOffFunction);
}

