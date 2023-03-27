#include "CAction_Combo_Branch.h"
#include "CHelpers.h"

#include "ActionFunctions.h"
#include "Notifies/CANS_Combo.h"
#include "Notifies/CAN_BeginCombo.h"
#include "Components/CStateComponent.h"
#include "Notifies/CANS_ReplaceAction.h"

UCAction_Combo_Branch::UCAction_Combo_Branch() : UCAction_Replacement(), ComboMaxIndex(0),
                                                 ComboIndex(0), bComboEnable(true), bInputExist(false)
{
}


void UCAction_Combo_Branch::BeginPlay()
{
	Super::BeginPlay();

	ComboMaxIndex = ActionDatas.Num();
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	//소유한 몽타주에서 노티파이 델리게이션 세팅
	for(FActionData ActionData : ActionDatas)
	{
		for(FAnimNotifyEvent AnimNotify : ActionData.Montage->Notifies)
		{
			if(AnimNotify.Notify != nullptr && AnimNotify.Notify->GetClass() == UCAN_BeginCombo::StaticClass())
			{
				Cast<UCAN_BeginCombo>(AnimNotify.Notify)->OnBeginCombo.BindUObject(this, &UCAction_Combo_Branch::BeginCombo);
			}
			else if(AnimNotify.NotifyStateClass != nullptr)
			{
				if(AnimNotify.NotifyStateClass->GetClass() == UCANS_Combo::StaticClass())
				{
					Cast<UCANS_Combo>(AnimNotify.NotifyStateClass)->OnEnableCombo.BindUObject(this, &UCAction_Combo_Branch::EnableCombo);
				}
			}
		}
	}
}

void UCAction_Combo_Branch::BeginAction()
{
	Super::BeginAction();

	StateComponent->SetActionMode();
	ActionFunctions::DoAction(ActionDatas[0], OwnerCharacter);
}

void UCAction_Combo_Branch::EndAction()
{
	Super::EndAction();
	
	ActionFunctions::EndAction(OwnerCharacter);
	StateComponent->SetIdleMode();
	ComboIndex = 0;
}

void UCAction_Combo_Branch::KeyPressed()
{
	Super::KeyPressed();

	if(!ActionDatas.IsValidIndex(0))
	{
		return;
	}

	//액션 도중 입력이 들어왔음
	if (bComboEnable)
	{
		bComboEnable = false;
		bInputExist = true;
		return;
	}

	if(StateComponent->IsIdleMode())
	{
		BeginAction();
	}
}


void UCAction_Combo_Branch::BeginCombo()
{
	if(ComboMaxIndex <= ComboIndex || !bInputExist)
	{
		return;
	}
	bInputExist = false;
	

	//SetCharacterDirectionToForward(OwnerCharacter);
	ComboIndex = (ComboIndex + 1) % ComboMaxIndex;
	
	if(ActionDatas.IsValidIndex(ComboIndex))
	{
		ActionFunctions::DoAction(ActionDatas[ComboIndex], OwnerCharacter);
	}
}

void UCAction_Combo_Branch::EnableCombo(bool InIsEnableCombo)
{
	bComboEnable = InIsEnableCombo;
}