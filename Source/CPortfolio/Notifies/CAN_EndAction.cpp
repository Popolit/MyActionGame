#include "CAN_EndAction.h"
#include "CHelpers.h"

#include "Components/CActionComponent.h"

UCAN_EndAction::UCAN_EndAction() : ActionType(EActionType::None), NotifyName("EndAction")
{
}

FString UCAN_EndAction::GetNotifyName_Implementation() const
{
	return NotifyName;
}

void UCAN_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(MeshComp == nullptr || MeshComp->GetOwner() == nullptr || ActionType == EActionType::None)
	{
		return;
	}
	
	UCActionComponent* ActionComponent = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	if(ActionComponent != nullptr)
	{
		ActionComponent->EndAction(ActionType, IsInAir);
	}
}
