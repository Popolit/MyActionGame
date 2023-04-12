#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_Collision.generated.h"


UINTERFACE()
class UCI_Collision : public UInterface
{
	GENERATED_BODY()
};

class ICI_Collision
{
	GENERATED_BODY()
public:
	virtual void OnCollision(AActor* InAttackCauser, AActor* InTargetActor) = 0;
};
