#include "CAIBehaviorComponent.h"
#include "CHelpers.h"


#include "CActionComponent.h"
#include "CStateComponent.h"
#include "Characters/CCharacter_Base.h"
#include "BehaviorTree/BlackboardComponent.h"

UCAIBehaviorComponent::UCAIBehaviorComponent() : TargetKey("Target"), BehaviorKey("Behavior")
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCAIBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	UCStateComponent* StateComponent = CHelpers::GetComponent<UCStateComponent>(GetOwner());
	check(StateComponent);
	
	StateComponent->OnStateTypeChanged.AddUObject(this, &UCAIBehaviorComponent::OnStateTypeChanged);

	ActionComponent = CHelpers::GetComponent<UCActionComponent>(GetOwner());
	check(ActionComponent);
}

bool UCAIBehaviorComponent::IsIdleMode() const
{
	return (EBehaviorType)GetBlackboard()->GetValueAsEnum(BehaviorKey) == EBehaviorType::Idle;
}

bool UCAIBehaviorComponent::IsChaseMode() const
{
	return (EBehaviorType)GetBlackboard()->GetValueAsEnum(BehaviorKey) == EBehaviorType::Chase;
}

bool UCAIBehaviorComponent::IsRetreatMode() const
{
	return (EBehaviorType)GetBlackboard()->GetValueAsEnum(BehaviorKey) == EBehaviorType::Retreat; 
}

bool UCAIBehaviorComponent::IsEvadeMode() const
{
	return (EBehaviorType)GetBlackboard()->GetValueAsEnum(BehaviorKey) == EBehaviorType::Evade;
}

bool UCAIBehaviorComponent::IsSubActionMode() const
{
	return (EBehaviorType)GetBlackboard()->GetValueAsEnum(BehaviorKey) == EBehaviorType::SubAction;
}

bool UCAIBehaviorComponent::IsActionMode() const
{
	return (EBehaviorType)GetBlackboard()->GetValueAsEnum(BehaviorKey) == EBehaviorType::Action;
}

bool UCAIBehaviorComponent::IsHitMode() const
{
	return (EBehaviorType)GetBlackboard()->GetValueAsEnum(BehaviorKey) == EBehaviorType::Hit;
}

bool UCAIBehaviorComponent::IsDeadMode() const
{
	return (EBehaviorType)GetBlackboard()->GetValueAsEnum(BehaviorKey) == EBehaviorType::Dead;
}

void UCAIBehaviorComponent::ChangeBehaviorType(EBehaviorType const& InBehaviorType)
{
	EBehaviorType BehaviorType = (EBehaviorType)GetBlackboard()->GetValueAsEnum(BehaviorKey);
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InBehaviorType);

	/*if (OnBehaviorTypeChanged.IsBound())
	{
		OnBehaviorTypeChanged.Broadcast(BehaviorType, InBehaviorType);
	}*/
}

void UCAIBehaviorComponent::SetIdleMode()
{
	ChangeBehaviorType(EBehaviorType::Idle);
}

void UCAIBehaviorComponent::SetChaseMode()
{
	ChangeBehaviorType(EBehaviorType::Chase);
}

void UCAIBehaviorComponent::SetReatreatMode()
{
	ChangeBehaviorType(EBehaviorType::Retreat);
}

void UCAIBehaviorComponent::SetEvadeMode()
{
	ChangeBehaviorType(EBehaviorType::Evade);
}

void UCAIBehaviorComponent::SetSubActionMode()
{
	ChangeBehaviorType(EBehaviorType::SubAction);
}

void UCAIBehaviorComponent::SetActionMode()
{
	ChangeBehaviorType(EBehaviorType::Action);
}

void UCAIBehaviorComponent::SetHitMode()
{
	ChangeBehaviorType(EBehaviorType::Hit);
}

void UCAIBehaviorComponent::SetDeadMode()
{
	ChangeBehaviorType(EBehaviorType::Dead);
}

void UCAIBehaviorComponent::OnStateTypeChanged(EStateType InStateType)
{
	switch(InStateType)
	{
		case EStateType::Idle:
		{
			SetIdleMode();
			break;
		}
		case EStateType::Evade:
		{
			SetEvadeMode();
			break;
		}
		case EStateType::Hit:
		{
			SetHitMode();
			break;
		}
		case EStateType::Dead:
		{
			SetDeadMode();
			break;
		}
	}
}


ACCharacter_Base* UCAIBehaviorComponent::GetTarget() const
{
	UObject* Target = Blackboard->GetValueAsObject(TargetKey);
	if(Target == nullptr)
	{
		return nullptr;
	}
	return Cast<ACCharacter_Base>(Target);
}

