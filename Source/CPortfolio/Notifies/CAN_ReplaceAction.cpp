#include "CAN_ReplaceAction.h"
#include "CHelpers.h"

#include "Components/CActionComponent.h"


UCAN_ReplaceAction::UCAN_ReplaceAction() : NotifyName("ReplaceAction")
{
}

FString UCAN_ReplaceAction::GetNotifyName_Implementation() const
{
	return NotifyName;
}

void UCAN_ReplaceAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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
		OnToggleEventTrigger.Execute(EventName, true);
	}
	else
	{
		OnToggleEventTrigger.Execute(EventName, true);
	}
}