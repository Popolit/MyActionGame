#include "CAction_Hitted_Aerial.h"

/*
#include "Global.h"
#include "Characters/CCharacter_Base.h"

#include "Components/CStateComponent.h"


void UCAction_Hitted_Aerial::BeginPlay(ACCharacter_Base* InOwner, TArray<FActionData> const& InActionMontages)
{
	Super::BeginPlay(InOwner, InActionMontages);
	
	OwnerCharacter->LandedDelegate.AddDynamic(this, &UCAction_Hitted_Aerial::OnLanded);
}
*/

/*
void UCAction_Hitted_Aerial::Pressed_Implementation()
{
	Super::Pressed_Implementation();
	
	Status->Stop();
	Status->StopAction();
	bHitted = true;
	
	if(!ActionMontages.IsValidIndex(0))
		return;
	ActionMontages[0].DoAction(OwnerCharacter);
}

void UCAction_Hitted_Aerial::EndAction_Implementation()
{
	Super::EndAction_Implementation();

	Status->Move();
	Status->Action();
	State->SetIdleMode();
	bHitted = false;
	
	if(!ActionMontages.IsValidIndex(0))
		return;
	ActionMontages[1].DoAction(OwnerCharacter);
}

void UCAction_Hitted_Aerial::OnLanded(const FHitResult& Hit)
{
	if(bHitted)
		EndAction_Implementation();
}
*/


