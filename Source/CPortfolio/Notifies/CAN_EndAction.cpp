#include "CAN_EndAction.h"
#include "Components/CActionComponent.h"

UCAN_EndAction::UCAN_EndAction() : NotifyName("EndAction")
{
}

FString UCAN_EndAction::GetNotifyName_Implementation() const
{
	return NotifyName;
}

void UCAN_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(OnEndAction.IsBound())
	{
		OnEndAction.Execute();
	}
}
