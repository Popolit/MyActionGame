#include "CAction_Evade.h"
#include "CHelpers.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CStateComponent.h"

UCAction_Evade::UCAction_Evade() : UAction(), MaxActionCount(2), CoolTime(1.0f)
{
}

void UCAction_Evade::BeginPlay()
{
	Super::BeginPlay();

	check(OwnerCharacter);
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
}


void UCAction_Evade::BeginAction()
{
	//ActionDatas[0].DoAction(OwnerCharacter);
	StateComponent->SetActionMode();
	ActionCountLeft--;
}

void UCAction_Evade::EndAction()
{
	Super::EndAction();
	StateComponent->SetIdleMode();
	CoolTimeLeft = CoolTime;
}


void UCAction_Evade::KeyPressed()
{
	CheckTrue(0 < ActionCountLeft);
	BeginAction();	
}

void UCAction_Evade::KeyReleased()
{
}

void UCAction_Evade::Tick(float const& InDeltaTime)
{
	CheckTrue(CoolTimeLeft <= 0.f);
	CoolTimeLeft -= InDeltaTime;
}

