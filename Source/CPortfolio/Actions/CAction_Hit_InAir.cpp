#include "CAction_Hit_InAir.h"
#include "CHelpers.h"
#include "ActionFunctions.h"

#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"


UCAction_Hit_InAir::UCAction_Hit_InAir() : EventName("Landed")
{
}

void UCAction_Hit_InAir::BeginPlay()
{
	Super::BeginPlay();
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	check(StateComponent);
	
	StatusComponent = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	check(StatusComponent);

	UCActionComponent* ActionComponent = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	check(ActionComponent);

	ActionComponent->BindActionEvent(EventName, this);
}

void UCAction_Hit_InAir::BeginAction()
{
	Super::BeginAction();
	if(ActionDatas.IsValidIndex(0))
	{
		ActionFunctions::DoAction(ActionDatas[0], OwnerCharacter);
	}
	StatusComponent->DisableAction();
}

void UCAction_Hit_InAir::EndAction()
{
	Super::EndAction();
	if(ActionDatas.IsValidIndex(0))
	{
		OwnerCharacter->PlayAnimMontage(ActionDatas[0].Montage, ActionDatas[0].PlayRatio, "Hit_LoopEnd");
	}
	StatusComponent->EnableAction();
	StateComponent->SetIdleMode();
}

void UCAction_Hit_InAir::HandleEvent()
{
	EndAction();
}