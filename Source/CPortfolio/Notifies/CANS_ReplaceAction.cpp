#include "CANS_ReplaceAction.h"
#include "CHelpers.h"

#include "Components/CActionComponent.h"


UCANS_ReplaceAction::UCANS_ReplaceAction() : NotifyName("ReplaceAction")
{
}

FString UCANS_ReplaceAction::GetNotifyName_Implementation() const
{
	return NotifyName;
}

void UCANS_ReplaceAction::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
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

void UCANS_ReplaceAction::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if(OnToggleEventTrigger.IsBound())
	{
		OnToggleEventTrigger.Execute(EventName, false);
	}
}
