#include "Actions/CAction_Guard.h"
#include "CHelpers.h"

#include "ActionFunctions.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"


UCAction_Guard::UCAction_Guard() : UCAction_Base(), bCanParry(false)
{
}

void UCAction_Guard::BeginPlay()
{
	Super::BeginPlay();
	
	check(OwnerCharacter);
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	check(StateComponent);
	
	UCActionComponent* ActionComponent = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	check(ActionComponent);

	//패링 가능 토글
	ActionComponent->BindActionEvent("CanParry", Cast<ICI_ToggleEventHandler>(this));
	//정면 공격 이벤트 등록
	ActionComponent->BindActionEvent("GetFrontAttack", Cast<ICI_EventHandler>(this));
}

void UCAction_Guard::BeginAction()
{
	Super::BeginAction();

	ActionFunctions::DoAction(ActionDatas[0], OwnerCharacter);
	StateComponent->SetSubActionMode();
}

void UCAction_Guard::EndAction()
{
	Super::EndAction();

	
	ActionFunctions::EndAction(OwnerCharacter);
	StateComponent->SetIdleMode();
}

void UCAction_Guard::KeyPressed()
{
	if(ActionDatas.IsValidIndex(0) && StateComponent->IsIdleMode())
	{
		BeginAction();
	}
}

void UCAction_Guard::KeyReleased()
{
	if(ActionDatas.IsValidIndex(1) && !bActionEnded)
    {
    	ActionFunctions::DoAction(ActionDatas[1], OwnerCharacter);
		EndAction();
    }
}

//정면 공격을 받음
void UCAction_Guard::HandleEvent()
{
	//패링
	if(bCanParry && ActionDatas.IsValidIndex(2))
	{
		ActionFunctions::DoAction(ActionDatas[2], OwnerCharacter);
	}
	else if(ActionDatas.IsValidIndex(3))
	{
		ActionFunctions::DoAction(ActionDatas[3], OwnerCharacter);
	}
}

//패링 온 오프
void UCAction_Guard::HandleEvent(bool IsEventOn)
{
	bCanParry = IsEventOn;
}



