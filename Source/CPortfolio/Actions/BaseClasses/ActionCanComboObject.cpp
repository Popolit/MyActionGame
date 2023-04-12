/*
#include "ActionCanComboObject.h"
#include "CHelpers.h"

#include "Notifies/CAN_BeginCombo.h"
#include "Notifies/CANS_Combo.h"
#include "Components/CStateComponent.h"


FActionCanComboObject::FActionCanComboObject(): ComboMaxIndex(0),
                                  ComboIndex(0), bComboEnable(false), bInputExist(false)
{
}


void FActionCanComboObject::SetComboDelegation(TArray<UAction*>& ActionDatas)
{
	ComboMaxIndex = ActionDatas.Num();
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	//소유한 몽타주에서 노티파이 델리게이션 세팅
	for(FActionData ActionData : ActionDatas)
	{
		for(FAnimNotifyEvent AnimNotify : ActionData.Montage->Notifies)
		{
			if(AnimNotify.Notify != nullptr && AnimNotify.Notify->GetClass() == UCAN_BeginCombo::StaticClass())
			{
				Cast<UCAN_BeginCombo>(AnimNotify.Notify)->OnBeginCombo.BindUObject(this, &UCAction_Combo::BeginCombo);
			}
			else if(AnimNotify.NotifyStateClass != nullptr && AnimNotify.NotifyStateClass->GetClass() == UCANS_Combo::StaticClass())
			{
				Cast<UCANS_Combo>(AnimNotify.NotifyStateClass)->OnEnableCombo.BindUObject(this, &UCAction_Combo::EnableCombo);
			}
		}
	}
}

void UCAction_Combo::BeginAction()
{
	Super::BeginAction();

	SetDirectionToCamera();
	StateComponent->SetActionMode();
	ActionFunctions::DoAction(ActionDatas[0], OwnerCharacter);
}

void UCAction_Combo::EndAction()
{
	Super::EndAction();
	ActionFunctions::EndAction(OwnerCharacter);
	StateComponent->SetIdleMode();
	ComboIndex = 0;
}

void UCAction_Combo::HandleKeyPressed()
{
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

	if(StateComponent->IsIdleMode() && bActionEnded)
	{
		BeginAction();
	}
}

void UCAction_Combo::OnCollision(AActor* InAttackCauser, AActor* InTargetActor)
{
	if(HitDatas.IsValidIndex(ComboIndex))
	{
		ActionFunctions::PlayHitEffect(HitDatas[ComboIndex], OwnerCharacter, InTargetActor);
		ActionFunctions::SendDamage(&HitDatas[ComboIndex], OwnerCharacter, InAttackCauser, InTargetActor);
	}
}

//노티파이가 실행할 함수, 최초 이후의 콤보 공격
void UCAction_Combo::BeginCombo()
{
	if(ComboMaxIndex <= ComboIndex || !bInputExist)
	{
		return;
	}
	bInputExist = false;
	

	SetDirectionToCamera();
	ComboIndex = (ComboIndex + 1) % ComboMaxIndex;
	
	if(ActionDatas.IsValidIndex(ComboIndex))
	{
		ActionFunctions::DoAction(ActionDatas[ComboIndex], OwnerCharacter);
	}
}

void UCAction_Combo::EnableCombo(bool InIsEnableCombo)
{
	bComboEnable = InIsEnableCombo;
}
*/
