#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_Action_Tick.generated.h"

class UCAction;
UINTERFACE()
class UCI_Action_Tick : public UInterface
{
	GENERATED_BODY()

};

class ICI_Action_Tick
{
	GENERATED_BODY()
public:
	UFUNCTION()
		virtual void Tick(float const& InDeltaTime) = 0;
};
