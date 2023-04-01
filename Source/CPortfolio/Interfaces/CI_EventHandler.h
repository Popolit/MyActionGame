#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_EventHandler.generated.h"


UINTERFACE()
class UCI_EventHandler : public UInterface
{
	GENERATED_BODY()
};

class ICI_EventHandler
{
	GENERATED_BODY()
public:
	virtual void HandleEvent() = 0;
};