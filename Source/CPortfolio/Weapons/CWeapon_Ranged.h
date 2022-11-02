#pragma once

#include "CoreMinimal.h"
#include "Weapons/CWeapon.h"
#include "CWeapon_Ranged.generated.h"

UCLASS()
class CPORTFOLIO_API ACWeapon_Ranged : public ACWeapon
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;
public:
	ACWeapon_Ranged();
};
