#include "CStateComponent.h"

#include "CActionComponent.h"
#include "CHelpers.h"

#include "CLog.h"

UCStateComponent::UCStateComponent()
{

}

void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	check(Owner);

	UCActionComponent* ActionComponent = CHelpers::GetComponent<UCActionComponent>(Owner);
	check(ActionComponent);
	
	OnToggleEventTrigger.BindUObject(ActionComponent, &UCActionComponent::OnActionEvent);
	OnAirborneEventTrigger.BindUObject(ActionComponent, &UCActionComponent::OnActionEvent);
	OnLandedEventTrigger.BindUObject(ActionComponent, &UCActionComponent::OnActionEvent);
}

void UCStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UCStateComponent::SetDashMode()
{
	ChangeType(EStateType::Dash);
}

void UCStateComponent::SetEvadeMode()
{
	ChangeType(EStateType::Evade);
}

void UCStateComponent::SetEquipMode()
{
	ChangeType(EStateType::Equip);
}

void UCStateComponent::SetSubActionMode()
{
	ChangeType(EStateType::SubAction);
}


void UCStateComponent::SetActionMode()
{
	ChangeType(EStateType::Action);
}

void UCStateComponent::SetHitMode()
{
	ChangeType(EStateType::Hit);
}

void UCStateComponent::SetDeadMode()
{
	ChangeType(EStateType::Dead);
}

//할일 : 델리게이션 이벤트 교체
void UCStateComponent::ChangeType(EStateType InType)
{
	if(Type == InType)
	{
		return;
	}
	
	EStateType PrevType = Type;
	Type = InType;
	
	if (OnStateTypeChanged.IsBound())
	{
		OnStateTypeChanged.Broadcast(Type);
	}

	if(OnToggleEventTrigger.IsBound())
	{
		switch(PrevType)
		{
			case EStateType::Dash:
			{
				OnToggleEventTrigger.Execute("Dash", false);	
				break;
			}
			case EStateType::SubAction:
			{
				OnToggleEventTrigger.Execute("SubAction", false);
				break;
			}
			case EStateType::Hit:
			{
				OnToggleEventTrigger.Execute("Hit", false);	
				break;
			}
		}
		switch(Type)
		{
			case EStateType::Dash:
			{
				OnToggleEventTrigger.Execute("Dash", true);	
				break;
			}
			case EStateType::SubAction:
			{
				OnToggleEventTrigger.Execute("SubAction", true);
				break;
			}
			case EStateType::Hit:
			{
				OnToggleEventTrigger.Execute("Hit", true);	
				break;
			}
		}
	}
	
	FString const ss[uint8(EStateType::Max) + 1] = {"Idle", "Dash", "Evade", "Equip", "SubAction", "Action", "Hitted", "Dead", "Max"};
	CLog::Print(ss[uint8(Type)]);
}


//True = IsInAir
//할일 : EventTrigger로 완전히 교체
void UCStateComponent::SetIsInAir(bool const& InAirCondition)
{
	if(bIsInAir == InAirCondition)
	{
		return;
	}
	bIsInAir = InAirCondition;
	if (OnAerialConditionChanged.IsBound())
		OnAerialConditionChanged.Broadcast(bIsInAir);

	if (OnAirborneEventTrigger.IsBound() && InAirCondition)
	{
		OnAirborneEventTrigger.Execute("Airborne");
	}
	if (OnLandedEventTrigger.IsBound() && !InAirCondition)
	{
		OnLandedEventTrigger.Execute("Landed");
	}
}
