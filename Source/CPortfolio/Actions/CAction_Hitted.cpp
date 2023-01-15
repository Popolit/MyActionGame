#include "CAction_Hitted.h"
#include "Global.h"
void UCAction_Hitted::Pressed_Implementation()
{
	Super::Pressed_Implementation();
	
	Status->Stop();
	Status->StopAction();
	bStaggering = true;
	if(ActionMontages.Num() == 0)
		return;
	
	ActionMontages[FMath::RandRange(0, ActionMontages.Num() - 1)].DoAction(OwnerCharacter);
}

void UCAction_Hitted::EndAction_Implementation()
{
	Super::EndAction_Implementation();
	bStaggering = false;
	State->SetIdleMode();
	Status->Move();
	Status->Action();
}

void UCAction_Hitted::Tick(float const& InDeltaTime)
{
	if(StaggerTimeLeft < 0.f)
	{
		if(bStaggering)
			EndAction_Implementation();
		return;
	}
	
	StaggerTimeLeft -= InDeltaTime;
}

void UCAction_Hitted::SetTickTime(float const& InTime)
{
	StaggerTimeLeft = InTime;
}
