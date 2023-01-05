#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CActionStructure.h"
#include "CI_Action_Collision.generated.h"

UINTERFACE()
class UCI_Action_Collision : public UInterface
{
	GENERATED_BODY()
};

class ICI_Action_Collision
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void GetHitData(FHitData& OutHitData);
	virtual void GetHitData_Implementation(FHitData& OutHitData) = 0;
};
