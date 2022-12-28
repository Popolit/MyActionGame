#include "CGuard.h"
#include "Global.h"

#include "Components/CStatusComponent.h"

UCGuard::UCGuard()
{
}

void UCGuard::BeginPlay(ACCharacter_Base* InOwner, const TArray<FActionMontage>& InActionMontages)
{
	Super::BeginPlay(InOwner, InActionMontages);
}

void UCGuard::Pressed_Implementation()
{
	Super::Pressed_Implementation();

	if(!ActionMontages.IsValidIndex(0))
		return;
	ActionMontages[0].DoAction(OwnerCharacter);
	State->SetGuardMode();
	Status->Stop();
}

void UCGuard::Released_Implementation()
{
	Super::Released_Implementation();

	if(bInterrupted)
		return;
	if(!ActionMontages.IsValidIndex(1))
		return;
	ActionMontages[1].DoAction(OwnerCharacter);
	EndAction();
}

void UCGuard::EndAction_Implementation()
{
	Super::EndAction_Implementation();
	State->SetIdleMode();
}

