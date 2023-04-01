#include "CAN_BeginCombo.h"
#include "Components/CActionComponent.h"

UCAN_BeginCombo::UCAN_BeginCombo() : NotifyName("BeginCombo")
{
}

FString UCAN_BeginCombo::GetNotifyName_Implementation() const
{
	return NotifyName;
}

void UCAN_BeginCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(OnBeginCombo.IsBound())
	{
		OnBeginCombo.Execute();
	}
}