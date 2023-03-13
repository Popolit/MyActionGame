#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_Action_CanBranch.generated.h"

class UAction;

UINTERFACE()
class UCI_Action_CanBranch : public UInterface
{
	GENERATED_BODY()
};

class ICI_Action_CanBranch
{
	GENERATED_BODY()
public:
	virtual void SetBranchAction(UAction* InBranchAction) = 0;
};