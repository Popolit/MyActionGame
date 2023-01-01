#include "CAction_Hitted.h"

void UCAction_Hitted::Pressed_Implementation()
{
	Super::Pressed_Implementation();
	
	Status->Stop();
	Status->StopAction();
	if(ActionMontages.Num() == 0)
		return;
	
	ActionMontages[FMath::RandRange(0, ActionMontages.Num() - 1)].DoAction(OwnerCharacter);
}

void UCAction_Hitted::EndAction_Implementation()
{
	Super::EndAction_Implementation();
	Status->Action();
}
