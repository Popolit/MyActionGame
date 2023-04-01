#include "CAN_RevertAction.h"
#include "CHelpers.h"

#include "Components/CActionComponent.h"


UCAN_RevertAction::UCAN_RevertAction() : NotifyName("RevertAction")
{
}

FString UCAN_RevertAction::GetNotifyName_Implementation() const
{
	return NotifyName;
}

void UCAN_RevertAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(!OnToggleEventTrigger.IsBound())
	{
		if(MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
		{
			return;
		}
		UCActionComponent* ActionComponent = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());

		if(ActionComponent == nullptr)
		{
			return;
		}
		
		OnToggleEventTrigger.BindUObject(ActionComponent, &UCActionComponent::OnActionEvent);
		OnToggleEventTrigger.Execute(EventName, false);
	}
	else
	{
		OnToggleEventTrigger.Execute(EventName, false);
	}
}