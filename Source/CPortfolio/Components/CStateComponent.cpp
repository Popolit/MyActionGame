#include "CStateComponent.h"
#include "Global.h"

UCStateComponent::UCStateComponent()
{

}

void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
	
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

void UCStateComponent::SetGuardMode()
{
	ChangeType(EStateType::Guard);
}

void UCStateComponent::SetZoomMode()
{
	ChangeType(EStateType::Zoom);
}

void UCStateComponent::SetActionMode()
{
	ChangeType(EStateType::Action);
}

void UCStateComponent::SetHittedMode()
{
	ChangeType(EStateType::Hitted);
}

void UCStateComponent::SetDeadMode()
{
	ChangeType(EStateType::Dead);
}

void UCStateComponent::ChangeType(EStateType InType)
{
	EStateType prevType = Type;
	Type = InType;
	
	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(Type);

	FString const ss[uint8(EStateType::Max) + 1] = {"Idle", "Dash", "Evade", "Equip", "Guard", "Zoom", "Action", "Hitted", "Dead", "Max"};
	CLog::Print(ss[uint8(Type)]);
}

//True = IsInAir
void UCStateComponent::SetIsInAir(bool const& InAirCondition)
{
	if(bIsInAir == InAirCondition)
		return;

	CLog::Print("IsInAir" + bIsInAir);
	bIsInAir = InAirCondition;
	if (OnAerialConditionChanged.IsBound())
		OnAerialConditionChanged.Broadcast(bIsInAir);
}
