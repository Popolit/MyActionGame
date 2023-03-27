#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_EventHandler_Toggle.generated.h"


UINTERFACE()
class UCI_EventHandler_Toggle : public UInterface
{
	GENERATED_BODY()
};

class ICI_EventHandler_Toggle
{
	GENERATED_BODY()
public:
	virtual void HandleEvent(bool IsEventOn) = 0;
};