#pragma once

#include "CoreMinimal.h"
#include "Weapons/CWeapon_Ranged.h"
#include "CWeapon_Ranged_Shotgun.generated.h"

UCLASS()
class CPORTFOLIO_API ACWeapon_Ranged_Shotgun : public ACWeapon_Ranged
{
	GENERATED_BODY()
public:
	ACWeapon_Ranged_Shotgun();
	
protected:
	virtual void BeginPlay() override;
	
};
