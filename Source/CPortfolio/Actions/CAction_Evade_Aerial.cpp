#include "CAction_Evade_Aerial.h"

#include "Characters/CCharacter_Base.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAction_Evade_Aerial::Pressed_Implementation()
{
	if(!ActionMontages.IsValidIndex(0))
		return;
	if(ActionCountLeft == 0)
		return;
	if(0.0f < CoolTimeLeft)
		return;
	
	ActionCountLeft--;
	State->SetEvadeMode();
	ActionMontages[0].DoAction(OwnerCharacter);
	OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UCAction_Evade_Aerial::EndAction_Implementation()
{
	Super::EndAction_Implementation();
	OwnerCharacter->GetCharacterMovement()->Velocity = FVector(0, 0, 0);
	OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
}