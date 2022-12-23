#include "CActionCombo_Aerial.h"
#include "Characters/CCharacter_Base.h"


UCActionCombo_Aerial::UCActionCombo_Aerial()
{
	ComboIndex = 0;
	bEnableAction = true;
	bComboEnable = false;
	bInputExist = false;
}

void UCActionCombo_Aerial::BeginPlay(ACCharacter_Base* InOwner, const TArray<FActionMontage>& InActionMontages)
{
	Super::BeginPlay(InOwner, InActionMontages);
	State->OnAerialConditionChanged.AddDynamic(this, &UCActionCombo_Aerial::OnAerialConditionChanged);
}

void UCActionCombo_Aerial::Pressed_Implementation()
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
	if(!bEnableAction)
		return;
	
	bEnableAction = false;
	State->SetActionMode();
	ActionMontages[0].DoAction(OwnerCharacter);
	
	OwnerCharacter->LaunchCharacter(FVector(0, 0, 120), false, true);
}

void UCActionCombo_Aerial::BeginCombo()
{
	Super::BeginCombo();
	OwnerCharacter->LaunchCharacter(FVector(0, 0, 120), false, true);
}



void UCActionCombo_Aerial::OnAerialConditionChanged(bool IsInAir)
{
	bEnableAction = true;
}



