#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter_Base.h"
#include "CEnemy.generated.h"

class UBehaviorTree;
class UCAIBehaviorComponent;

UCLASS()
class CPORTFOLIO_API ACEnemy : public ACCharacter_Base
{
	GENERATED_BODY()
public:
	ACEnemy();

private:
	UPROPERTY(VisibleDefaultsOnly)
		UCAIBehaviorComponent* BehaviorComponent;
};
