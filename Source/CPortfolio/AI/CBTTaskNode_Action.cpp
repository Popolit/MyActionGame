#include "CBTTaskNode_Action.h"
#include "CHelpers.h"

#include "Characters/CAIController.h"
#include "Components/CActionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CAIBehaviorComponent.h"
#include "Characters/CCharacter_Base.h"

UCBTTaskNode_Action::UCBTTaskNode_Action()
{
	bNotifyTick = true;

	NodeName = "Action";
}

EBTNodeResult::Type UCBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* AIController = Cast<ACAIController>(OwnerComp.GetOwner());
	UCActionComponent* ActionComponent = CHelpers::GetComponent<UCActionComponent>( AIController->GetPawn());

	
	if(ActionComponent != nullptr)
	{
		ActionComponent->KeyPressed(EActionType::Action);
	}
	
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UCBTTaskNode_Action::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACAIController* AIController = Cast<ACAIController>(OwnerComp.GetOwner());
	check(AIController);
	
	AIController->ClearFocus(EAIFocusPriority::Gameplay);
	return Super::AbortTask(OwnerComp, NodeMemory);
}

