#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_StateTrigger.generated.h"

UINTERFACE()
class UCI_StateTrigger : public UInterface
{
	GENERATED_BODY()
};

class ICI_StateTrigger
{
	GENERATED_BODY()
public:
	virtual void StateChanged() = 0;
};