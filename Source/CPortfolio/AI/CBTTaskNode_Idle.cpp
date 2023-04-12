#include "CBTTaskNode_Idle.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CAIController.h"

UCBTTaskNode_Idle::UCBTTaskNode_Idle()
{
	bNotifyTick = true;

	NodeName = "Idle";
}

EBTNodeResult::Type UCBTTaskNode_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* AIController = Cast<ACAIController>(OwnerComp.GetOwner());

	return EBTNodeResult::Succeeded;
}

