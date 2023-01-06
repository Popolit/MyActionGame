#include "CActionComponent.h"

#include "CWeaponComponent.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"
#include "Actions/CAction.h"
#include "Actions/CI_Action_Collision.h"
#include "Actions/CI_Action_Tick.h"
#include "Weapons/CAttachment.h"


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
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);

	//델리게이션
	state->OnStateTypeChanged.AddDynamic(this, &UCActionComponent::SetStateTrigger);
	state->OnAerialConditionChanged.AddDynamic(this, &UCActionComponent::SetAerialTrigger);
	WeaponComponent->OnWeaponTypeChanged.AddUObject(this, &UCActionComponent::OnWeaponChanged);
	OnActionInput.BindUObject(this, &UCActionComponent::ExecuteActionInput);
	
	ActionData = WeaponComponent->GetActionData();
}

void UCActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckNull(ActionData);
	for(UCAction* action : ActionData->GetTickableActions())
		Cast<ICI_Action_Tick>(action)->Tick(DeltaTime);
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

void UCActionComponent::OnWeaponChanged(EWeaponType PrevWeaponType, EWeaponType NewWeaponType)
{
	ActionData = WeaponComponent->GetActionData();
	for(ACAttachment* attachment : *WeaponComponent->GetAttachments())
	{
		attachment->OnAttachmentBeginOverlap.BindUObject(this, &UCActionComponent::OnAttachmentBeginOverlap);
		attachment->OnAttachmentEndOverlap.BindUObject(this, &UCActionComponent::OnAttachmentEndOverlap);
	}
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
//      Overlap Event
//  *********************

void UCActionComponent::OnAttachmentBeginOverlap(ACCharacter_Base* InAttacker, AActor* InAttackCauser, ACCharacter_Base* InOtherCharacter)
{
	CheckFalse((*RecentAction)->GetClass()->ImplementsInterface(UCI_Action_Collision::StaticClass()));

	FHitData hitData;
	ICI_Action_Collision::Execute_GetHitData(*RecentAction, hitData);

	CheckNull(InOtherCharacter);
	hitData.SendDamage(InAttacker, InAttackCauser, InOtherCharacter);
}

void UCActionComponent::OnAttachmentEndOverlap(ACCharacter_Base* InAttacker, AActor* InAttackCauser, ACCharacter_Base* InOtherCharacter)
{
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



