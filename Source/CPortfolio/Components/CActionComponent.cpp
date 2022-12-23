#include "CActionComponent.h"

#include "CWeaponComponent.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"
#include "Weapons/Actions/CAction.h"


//  *********************
//      기본 세팅
//  *********************
UCActionComponent::UCActionComponent()
{
}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	//오너 캐릭터 세팅
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	CheckNull(OwnerCharacter);


	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	state->OnStateTypeChanged.AddDynamic(this, &UCActionComponent::SetStateTrigger);
	state->OnAerialConditionChanged.AddDynamic(this, &UCActionComponent::SetAerialTrigger);
	WeaponComponent->OnWeaponTypeChanged.AddUObject(this, &UCActionComponent::SetActionData);
	OnActionInput.BindUObject(this, &UCActionComponent::ExecuteActionInput);
}

//  **********************
//      Action & Trigger
//  **********************

UCAction* UCActionComponent::GetAction(EActionType const & InActionInput)
{
	CheckNullResult(Actions[(uint8)InActionInput], nullptr);
	return Actions[(uint8)InActionInput];
}

//State가 변경 시 호출, State에 따라 Action을 트리거
void UCActionComponent::SetStateTrigger(EStateType InStateType)
{
	Trigger.StateType = InStateType;
	ExecuteActionInput(EActionType::None, true);
}

void UCActionComponent::SetAerialTrigger(bool IsInAir)
{
	Trigger.IsInAir = IsInAir;
	ExecuteActionInput(EActionType::None, true);
}

void UCActionComponent::SetActionTrigger(EActionType InActionType)
{
	Trigger.ActionType = InActionType;
}

void UCActionComponent::SetActionData(EWeaponType PrevWeaponType, EWeaponType NewWeaponType)
{
	ActionData = WeaponComponent->GetActionData();
}

//Action 변경되면 true
bool UCActionComponent::SetAction()
{
	CheckNullResult(ActionData, false);
	FActionTrigger trigger = Trigger;
	UCAction* newAction = ActionData->GetAction(trigger);
	
	CheckNullResult(newAction, false);
	if(newAction == Actions[(uint8)trigger.ActionType])
		return true;
	
	
	if(OnActionChanged.IsBound())
		OnActionChanged.Broadcast(Actions[(uint8)trigger.ActionType], newAction);

	
	if(RecentAction != nullptr && (*RecentAction) != nullptr)
	{
		(*RecentAction)->EndAction();
		(*RecentAction) = nullptr;
		RecentAction = nullptr;
	}
	Actions[(uint8)trigger.ActionType] = newAction;
	RecentAction = &Actions[(uint8)trigger.ActionType];
	
	return true;
}

void UCActionComponent::EndAction(EActionType const & InActionInput)
{
	CheckNull(Actions[(uint8)InActionInput]);
	Actions[(uint8)InActionInput]->EndAction();
	Actions[(uint8)InActionInput] = nullptr;

	if(*RecentAction == nullptr)
		RecentAction = nullptr;
}

//  *********************
//      Inputs
//  *********************

void UCActionComponent::ExecuteActionInput(EActionType InActionInput, bool InPressed)
{
	if(InPressed)
	{
		SetActionTrigger(InActionInput);
		if(!SetAction())
			return;
		Pressed(InActionInput);
	}
	else
		Released(InActionInput);
}

void UCActionComponent::Pressed(EActionType const & InActionInput)
{
	CheckNull(Actions[(uint8)InActionInput]);
	Actions[(uint8)InActionInput]->Pressed();
}

void UCActionComponent::Released(EActionType const & InActionInput)
{
	CheckNull(Actions[(uint8)InActionInput]);
	Actions[(uint8)InActionInput]->Released();
}



