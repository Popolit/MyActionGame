#include "CActionComponent.h"

#include "CHelpers.h"

#include "Characters/Player/CPlayer.h"


//  *********************
//      기본 세팅
//  *********************
UCActionComponent::UCActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();
	//오너 캐릭터 세팅
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	CheckNull(OwnerCharacter);

	//컴포넌트 세팅
	/*UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	StatusComponent = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	
	//델리게이션
	state->OnStateTypeChanged.AddDynamic(this, &UCActionComponent::SetStateTrigger);
	state->OnAerialConditionChanged.AddDynamic(this, &UCActionComponent::SetAerialTrigger);
	WeaponComponent->OnWeaponTypeChanged.AddUObject(this, &UCActionComponent::OnWeaponChanged);
	OnActionInput.BindUObject(this, &UCActionComponent::ExecuteActionInput);
	
	ActionData = WeaponComponent->GetActionData();*/
}

void UCActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	/*for(TScriptInterface<ICI_Tickable> Action : Actions_Tickable)
		Action->Tick(DeltaTime);*/
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

void UCActionComponent::EndAction(EActionType const & InActionInput)
{
	CheckNull(Actions[(uint8)InActionInput]);
	Actions[(uint8)InActionInput]->EndAction();
	Actions[(uint8)InActionInput] = nullptr;

	if(*RecentAction == nullptr)
		RecentAction = nullptr;
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



