#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IKeyTrigger.generated.h"

UINTERFACE()
class UIKeyTrigger : public UInterface
{
	GENERATED_BODY()
};

class IIKeyTrigger
{
	GENERATED_BODY()
public:
	virtual void KeyPressed() = 0;
	virtual void KeyReleased() = 0;
};