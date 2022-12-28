#include "CAction_Jump.h"

#include "Characters/CCharacter_Base.h"

void UCAction_Jump::Pressed_Implementation()
{
	Super::Pressed_Implementation();
	if(!OwnerCharacter->CanJump())
		return;
	OwnerCharacter->Jump();
	if(ActionMontages.IsValidIndex(0))
		ActionMontages[0].DoAction(OwnerCharacter);
}

void UCAction_Jump::Released_Implementation()
{
	Super::Released_Implementation();
	OwnerCharacter->StopJumping();
}

