#include "CAction_Combo.h"
#include "CHelpers.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CStateComponent.h"

void UCAction_Combo::BeginPlay()
{
	Super::BeginPlay();
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	ComboIndex = 0;
	bComboEnable = true;
	bInputExist = false;
}

void UCAction_Combo::BeginAction()
{
	Super::BeginAction();
	//SetCharacterDirectionToForward(OwnerCharacter);
	StateComponent->SetActionMode();
	//ActionDatas[0].DoAction(OwnerCharacter);
}

void UCAction_Combo::EndAction()
{
	Super::EndAction();
	ComboIndex = 0;
	StateComponent->SetIdleMode();
}

void UCAction_Combo::KeyPressed()
{
	CheckFalse(ActionDatas.IsValidIndex(0));

	//액션 도중 입력이 들어왔음
	if (bComboEnable)
	{
		bComboEnable = false;
		bInputExist = true;
		return;
	}

	CheckFalse(StateComponent->IsIdleMode());
	BeginAction();
}

void UCAction_Combo::KeyReleased()
{
}

void UCAction_Combo::BeginCombo()
{
	CheckTrue(ComboMax == 0);
	CheckFalse(bInputExist);
	bInputExist = false;
	

	//SetCharacterDirectionToForward(OwnerCharacter);
	ComboIndex = (ComboIndex + 1) % ComboMax;
	
	if(ActionDatas.IsValidIndex(ComboIndex))
	{
		//ActionDatas[ComboIndex].DoAction(OwnerCharacter);
	}
}