#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Hit.generated.h"

UCLASS()
class CPORTFOLIO_API UCBTTaskNode_Hit : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_Hit();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
