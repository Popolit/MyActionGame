#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_Action_Collision.generated.h"

class ACCharacter_Base;

UINTERFACE()
class UCI_Action_Collision : public UInterface
{
	GENERATED_BODY()
};

class ICI_Action_Collision
{
	GENERATED_BODY()

public:
	virtual void SetCharacterDirectionToForward(ACCharacter_Base* InCharacter) = 0;
};


