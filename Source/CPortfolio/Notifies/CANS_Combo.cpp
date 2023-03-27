#include "CANS_Combo.h"



UCANS_Combo::UCANS_Combo() : NotifyName("Combo")
{
}

FString UCANS_Combo::GetNotifyName_Implementation() const
{
	return NotifyName;
}

void UCANS_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if(MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
	{
		return;
	}

	if(OnEnableCombo.IsBound())
	{
		OnEnableCombo.Execute(true);
	}
}

void UCANS_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
	{
		return;
	}

	if(OnEnableCombo.IsBound())
	{
		OnEnableCombo.Execute(false);
	}
}
