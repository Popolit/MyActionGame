#include "CAN_ActionEvent.h"
#include "CHelpers.h"

#include "Components/CActionComponent.h"

UCAN_ActionEvent::UCAN_ActionEvent() : NotifyName("ActionEvent")
{
}

FString UCAN_ActionEvent::GetNotifyName_Implementation() const
{
	return NotifyName;
}

void UCAN_ActionEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//델리게이션이 없으면 델리게이트 연결 후 실행
	if(!OnEventTrigger.IsBound())
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
		
		OnEventTrigger.BindUObject(ActionComponent, &UCActionComponent::OnActionEvent);
		OnEventTrigger.Execute(EventName);
	}
	else
	{
		OnEventTrigger.Execute(EventName);
	}
}
