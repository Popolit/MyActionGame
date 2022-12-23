#include "CActionCombo.h"
#include "Characters/CCharacter_Base.h"

UCActionCombo::UCActionCombo()
{
	ComboIndex = 0;
	bComboEnable = false;
	bInputExist = false;
}

void UCActionCombo::BeginPlay(ACCharacter_Base* InOwner, const TArray<FActionMontage>& InActionMontages)
{
	Super::BeginPlay(InOwner, InActionMontages);
}


//최초 타격
void UCActionCombo::Pressed_Implementation()
{
	if(!ActionMontages.IsValidIndex(0))
		return;
	if (bComboEnable)
	{
		bComboEnable = false;
		bInputExist = true;
		return;
	}
	if(!State->IsIdleMode())
		return;
	
	State->SetActionMode();
	ActionMontages[0].DoAction(OwnerCharacter);
}

void UCActionCombo::EndAction_Implementation()
{
	Super::EndAction_Implementation();
	ComboIndex = 0;
	State->SetIdleMode();
}

//콤보 어택
void UCActionCombo::BeginCombo()
{
	if(!bInputExist)
		return;
	bInputExist = false;

	if(ComboMax == 0)
		return;
	ComboIndex = (ComboIndex + 1) % ComboMax;
	
	if(ActionMontages.IsValidIndex(ComboIndex))
		ActionMontages[ComboIndex].DoAction(OwnerCharacter);
}

void UCActionCombo::SetComboEnable(bool IsComboEnable)
{
	bComboEnable = IsComboEnable;
}



