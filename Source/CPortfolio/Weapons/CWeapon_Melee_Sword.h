#pragma once

#include "CoreMinimal.h"
#include "Weapons/CWeapon_Melee.h"
#include "CWeapon_Melee_Sword.generated.h"

UCLASS()
class CPORTFOLIO_API ACWeapon_Melee_Sword : public ACWeapon_Melee
{
	GENERATED_BODY()
	
public:
	ACWeapon_Melee_Sword();
	
protected:
	virtual void BeginPlay() override;
};
