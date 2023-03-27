#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_EventListener.generated.h"



DECLARE_DELEGATE_OneParam(FOnEventTrigger, FName const&)
DECLARE_DELEGATE_TwoParams(FOnToggleEventTrigger, FName const&, bool const&)

UINTERFACE()
class UCI_EventListener : public UInterface
{
	GENERATED_BODY()
};

class ICI_EventListener
{
	GENERATED_BODY()
};