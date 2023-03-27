#include "CActionComponent.h"
#include "CHelpers.h"

#include "Characters/CCharacter_Base.h"
#include "Action.h"
#include "ActionSet.h"
#include "Weapon.h"
#include "CWeaponComponent.h"
#include "ITickable.h"
#include "Interfaces/CI_EventHandler.h"
#include "Interfaces/CI_EventHandler_Toggle.h"


UCActionComponent::UCActionComponent() : ActionSet(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	check(OwnerCharacter);

	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	if(!WeaponComponent->HasBegunPlay())
	{
		WeaponComponent->BeginPlay();
	}
	WeaponComponent->OnWeaponChanged.AddUObject(this, &UCActionComponent::OnWeaponChanged);
	ActionSet = WeaponComponent->GetWeapon()->GetActionSet();

	if(ActionSet != nullptr)
	{
		ActionSet->SetAllDelegations<UCActionComponent>(this, &UCActionComponent::OnActionBegin);
	}
}

void UCActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(ActionSet == nullptr)
	{
		return;
	}
	
	for(TScriptInterface<IITickable> Action_Tickable : ActionSet->GetActionsTickable())
	{
		Action_Tickable->Tick(DeltaTime);
	}
}

void UCActionComponent::BindActionEvent(FName const& InEventName, ICI_EventHandler* InEventHandler)
{
	
	ActionEvents.Add(InEventName, Cast<UAction>(InEventHandler));
}

void UCActionComponent::BindActionEvent(FName const& InEventName, ICI_EventHandler_Toggle* InEventHandler)
{
	ActionToggleEvents.Add(InEventName, Cast<UAction>(InEventHandler));
}

void UCActionComponent::OnWeaponChanged(UWeapon* PrevWeapon, UWeapon* NewWeapon)
{
	if(CurrAction != nullptr && !CurrAction->IsActionEnded())
	{
		CurrAction->EndAction();
	}
	ActionSet->UnsetAllDelegations();
	ActionSet = NewWeapon->GetActionSet();
	if(ActionSet != nullptr)
	{
		ActionSet->SetAllDelegations<UCActionComponent>(this, &UCActionComponent::OnActionBegin);
	}
}

void UCActionComponent::OnActionBegin(UAction* InAction)
{
	if(CurrAction != nullptr && !CurrAction->IsActionEnded())
	{
		CurrAction->EndAction();
	}
	CurrAction = InAction;
}

void UCActionComponent::OnActionEvent(FName const& InEventName)
{
	if(ActionEvents.Contains(InEventName))
	{
		ICI_EventHandler* EventHandler = Cast<ICI_EventHandler>(ActionEvents[InEventName]);
		if(EventHandler != nullptr)
		{
			EventHandler->HandleEvent();
		}
	}
}

void UCActionComponent::OnActionEvent(FName const& InEventName, bool const& IsEventOn)
{
	if(ActionToggleEvents.Contains(InEventName))
	{
		ICI_EventHandler_Toggle* EventHandler = Cast<ICI_EventHandler_Toggle>(ActionToggleEvents[InEventName]);
		if(EventHandler != nullptr)
		{
			EventHandler->HandleEvent(IsEventOn);
		}
	}
}


void UCActionComponent::KeyPressed(EActionType const& InActionInput)
{
	if(ActionSet == nullptr)
	{
		return;
	}

	UAction* PrevAction = CurrAction;
	//Air Action
	if(OwnerCharacter->IsInAir())
	{
		UAction* Action = ActionSet->GetActionsInAir()[(uint8)InActionInput];
		if(Action != nullptr)
		{
			CurrAction = Action;
			CurrAction->KeyPressed();
		}
	}
	//Ground Action
	else
	{
		UAction* Action = ActionSet->GetActions()[(uint8)InActionInput];
		if(Action != nullptr)
		{
			CurrAction = Action;
			CurrAction->KeyPressed();
		}
	}
}

void UCActionComponent::KeyReleased(EActionType const& InActionInput) const
{
	if(ActionSet == nullptr)
	{
		return;
	}
	UAction* Action = ActionSet->GetActions()[(uint8)InActionInput];
	if(Action != nullptr)
	{
		Action->KeyReleased();
	}
}

void UCActionComponent::EndAction(EActionType const& InActionInput, bool IsInAir)
{
	if(IsInAir)
	{
		UAction* Action = ActionSet->GetActionsInAir()[(uint8)InActionInput];
		if(Action != nullptr)
		{
			Action->EndAction();
		}
	}
	else
	{
		UAction* Action = ActionSet->GetActions()[(uint8)InActionInput];
		if(Action != nullptr)
		{
			Action->EndAction();
		}
	}
}


/*
void UCActionComponent::KeyPressed(EActionType const& InActionInput)
{
	/*ICI_KeyTrigger* Action = Cast<ICI_KeyTrigger>(Actions_TriggeredByKey[InActionInput]);
	CheckNull(Action);
	Action->KeyPressed();#1#
}

void UCActionComponent::KeyReleased(EActionType const& InActionInput)
{
	/*ICI_KeyTrigger* Action = Cast<ICI_KeyTrigger>(Actions_TriggeredByKey[InActionInput]);
	CheckNull(Action);
	Action->KeyReleased();#1#
}

void UCActionComponent::StateChanged(EStateType NewStateType)
{
	/*ICI_StateTrigger* Action = Cast<ICI_StateTrigger>(Actions_TriggeredByState[NewStateType]);
	CheckNull(Action);
	Action->StateChanged();#1#
}*/
/*
//  **********************
//      Action & Trigger
//  **********************

UCAction_Base* UCActionComponent::GetAction(EActionType const & InActionInput)
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

void UCActionComponent::OnWeaponChanged(EWeaponType PrevWeaponType, EWeaponType NewWeaponType)
{
	ActionData = WeaponComponent->GetActionData();
	CheckNull(ActionData);
	for(ACAttachment* attachment : *WeaponComponent->GetAttachments())
	{
		attachment->OnAttachmentBeginOverlap.BindUObject(this, &UCActionComponent::OnAttachmentBeginOverlap);
		attachment->OnAttachmentEndOverlap.BindUObject(this, &UCActionComponent::OnAttachmentEndOverlap);
		attachment->OffAttachmentCollision.BindUObject(this, &UCActionComponent::OnAttachmentOffCollision);
	}
}

//Action 변경되면 true
bool UCActionComponent::SetAction()
{
	CheckNullResult(ActionData, false);
	FActionTrigger trigger = Trigger;
	UCAction_Base* newAction = ActionData->GetAction(trigger);
	
	CheckNullResult(newAction, false);
	if(newAction == Actions[(uint8)trigger.ActionType])
		return true;

	if(!StatusComponent->CanAction())
		return false;
	
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



//  *********************
//      Overlap Event
//  *********************

void UCActionComponent::OnAttachmentBeginOverlap(ACCharacter_Base* InAttacker, AActor* InAttackCauser, ACCharacter_Base* InOtherCharacter)
{
	CheckFalse((*RecentAction)->GetClass()->ImplementsInterface(UCI_Action_Collision::StaticClass()));

	if(Arr_Hitted.Contains(InOtherCharacter))
		return;

	Arr_Hitted.Add(InOtherCharacter);
	FHitData hitData;
	ICI_Action_Collision::Execute_GetHitData(*RecentAction, hitData);

	CheckNull(InOtherCharacter);
	hitData.SendDamage(InAttacker, InAttackCauser, InOtherCharacter);
}

void UCActionComponent::OnAttachmentEndOverlap(ACCharacter_Base* InAttacker, AActor* InAttackCauser, ACCharacter_Base* InOtherCharacter)
{
}

void UCActionComponent::OnAttachmentOffCollision()
{
	Arr_Hitted.Empty();
}


//  *********************
//      Inputs
//  *********************

void UCActionComponent::ExecuteActionInput(EActionType InActionInput, bool InPressed)
{
	if(InPressed)
	{
		SetActionTrigger(InActionInput);
		if(SetAction())
			KeyPressed(InActionInput);
	}
	else
		KeyReleased(InActionInput);
}

void UCActionComponent::KeyPressed(EActionType const & InActionInput)
{
	CheckNull(Actions[(uint8)InActionInput]);
	Actions[(uint8)InActionInput]->Pressed();
}

void UCActionComponent::KeyReleased(EActionType const & InActionInput)
{
	CheckNull(Actions[(uint8)InActionInput]);
	Actions[(uint8)InActionInput]->Released();
}
*/



