#include "CAction_Jump.h"

#include "ActionFunctions.h"
#include "Characters/CCharacter_Base.h"


void UCAction_Jump::BeginAction()
{
	OwnerCharacter->Jump();
	if(!ActionDatas.IsValidIndex(0))
	{
		return;
	}

	ActionFunctions::DoAction(ActionDatas[0], OwnerCharacter);
}

void UCAction_Jump::KeyPressed()
{
	if(OwnerCharacter->CanJump())
	{
		BeginAction();
	}
}

void UCAction_Jump::KeyReleased()
{
	OwnerCharacter->StopJumping();
}
