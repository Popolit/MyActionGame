#pragma once

#include "CoreMinimal.h"
#include "Weapons/CWeapon.h"
#include "CWeapon_Melee.generated.h"

UCLASS()
class CPORTFOLIO_API ACWeapon_Melee : public ACWeapon
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

		
public:
	ACWeapon_Melee();
};
