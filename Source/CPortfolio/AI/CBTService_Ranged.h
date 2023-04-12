#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Ranged.generated.h"

UCLASS()
class CPORTFOLIO_API UCBTService_Ranged : public UBTService
{
	GENERATED_BODY()
public:
	UCBTService_Ranged();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	UPROPERTY(EditDefaultsOnly)
		float ActionRange;
	UPROPERTY(EditDefaultsOnly)
		float RetreatRange;

};
