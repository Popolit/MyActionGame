#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_ToggleEventHandler.generated.h"


UINTERFACE()
class UCI_ToggleEventHandler : public UInterface
{
	GENERATED_BODY()
};

class ICI_ToggleEventHandler
{
	GENERATED_BODY()
public:
	virtual void HandleEvent(bool IsEventOn) = 0;
};