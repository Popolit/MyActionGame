#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IKeyInput.generated.h"

/* Interface for Object Need KeyInput */
UINTERFACE()
class ACTIONSTRUCTURE_API UIKeyInput : public UInterface
{
	GENERATED_BODY()
};

class ACTIONSTRUCTURE_API IIKeyInput
{
	GENERATED_BODY()
public:
	virtual void KeyPressed() = 0;
	virtual void KeyReleased() = 0;
};
