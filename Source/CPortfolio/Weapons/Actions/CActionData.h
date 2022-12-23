#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CActionStructure.h"
#include "CActionData.generated.h"

UCLASS()
class CPORTFOLIO_API UCActionData : public UObject
{
	GENERATED_BODY()

private:
	friend class UCActionAsset;

public:
	UCAction* GetAction(FActionTrigger const& Trigger);

private:
	UPROPERTY()
		TMap<FActionTrigger, class UCAction*> Actions;
};
