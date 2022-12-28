#include "CAction_Evade.h"
#include "Characters/CCharacter_Base.h"

void UCAction_Evade::BeginPlay(ACCharacter_Base* InOwner, const TArray<FActionMontage>& InActionMontages)
{
	Super::BeginPlay(InOwner, InActionMontages);
	ActionCountLeft = MaxActionCount;
}

void UCAction_Evade::Tick(float const& InDeltaTime)
{
	if(0.0f < CoolTimeLeft)
		CoolTimeLeft -= InDeltaTime;
}

void UCAction_Evade::Pressed_Implementation()
{
	Super::Pressed_Implementation();
	
	if(!ActionMontages.IsValidIndex(0))
		return;
	if(ActionCountLeft == 0)
		return;
	if(0.0f < CoolTimeLeft)
		return;
	
	ActionCountLeft--;
	State->SetEvadeMode();
	ActionMontages[0].DoAction(OwnerCharacter);
}

void UCAction_Evade::EndAction_Implementation()
{
	Super::EndAction_Implementation();
	
	State->SetIdleMode();
	if(ActionCountLeft == MaxActionCount)
		return;
	CoolTimeLeft = CoolTime;
	ActionCountLeft = MaxActionCount;
}
