#include "CBTService_Melee.h"
#include "CHelpers.h"

#include "Characters/CAIController.h"
#include "Characters/CCharacter_Base.h"
#include "Components/CStateComponent.h"
#include "Components/CAIBehaviorComponent.h"

UCBTService_Melee::UCBTService_Melee() : ActionRange(150.0f)
{
	NodeName = "Service_Melee";

	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* AIController = Cast<ACAIController>(OwnerComp.GetOwner());
	ACCharacter_Base* OwnerCharacter = Cast<ACCharacter_Base>(AIController->GetPawn());
	check(OwnerCharacter);
	
	UCAIBehaviorComponent* BehaviorComponent = CHelpers::GetComponent<UCAIBehaviorComponent>(OwnerCharacter);
	check(BehaviorComponent);

	if(BehaviorComponent->IsHitMode() || BehaviorComponent->IsDeadMode() || OwnerCharacter->GetCurrentMontage() != nullptr)
	{
		return;
	}

	
	
	ACCharacter_Base* Target = BehaviorComponent->GetTarget();

	if(Target == nullptr)
	{
		BehaviorComponent->SetIdleMode();
		return;	
	}


	float DistanceToTarget = OwnerCharacter->GetDistanceTo(Target);
	if (DistanceToTarget < ActionRange)
	{
		BehaviorComponent->SetActionMode();
	}
	else
	{
		BehaviorComponent->SetChaseMode();
	}
}