#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CActionStructure.h"
#include "CI_Action_Tick.h"
#include "CActionData.generated.h"

UCLASS()
class CPORTFOLIO_API UCActionData : public UObject
{
	GENERATED_BODY()

private:
	friend class UCActionAsset;

public:
	FORCEINLINE UCAction* GetAction(FActionTrigger const& Trigger);
	FORCEINLINE TArray<UCAction*> const& GetTickableActions() { return TickableActions; };

private:
	UPROPERTY()
		TMap<FActionTrigger, class UCAction*> Actions;
	UPROPERTY()
		TArray<UCAction*> TickableActions;
};
