#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_Action_HasCollision.generated.h"


UINTERFACE()
class UCI_Action_HasCollision : public UInterface
{
	GENERATED_BODY()
};

class ICI_Action_HasCollision
{
	GENERATED_BODY()
public:
	virtual void OnCollision(AActor* InAttackCauser, AActor* InTargetActor) = 0;
};
