#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_WeaponHasFABRIK.generated.h"

/* Implement this When Weapon Need To Return FABRIK Transform */
UINTERFACE()
class UCI_WeaponHasFABRIK : public UInterface
{
	GENERATED_BODY()
};

class CPORTFOLIO_API ICI_WeaponHasFABRIK
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		FTransform GetFABRIKTransform() const;
};
