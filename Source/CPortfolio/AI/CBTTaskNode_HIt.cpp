#include "CBTTaskNode_Hit.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CAIController.h"

UCBTTaskNode_Hit::UCBTTaskNode_Hit()
{
	bNotifyTick = true;

	NodeName = "Hit";
}

EBTNodeResult::Type UCBTTaskNode_Hit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* AIController = Cast<ACAIController>(OwnerComp.GetOwner());
	AIController->StopMovement();

	return EBTNodeResult::InProgress;
}

